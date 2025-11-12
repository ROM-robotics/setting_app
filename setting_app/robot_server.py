#!/usr/bin/env python3
"""
Robot WiFi Management Server
This script should run on the Ubuntu 22.04 robot computer
It provides HTTP API and Bluetooth server for WiFi management
"""

import json
import subprocess
import threading
import time
import bluetooth
from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class WiFiManager:
    def get_wifi_status(self):
        """Get current WiFi connection status with IP address"""
        try:
            # Get current WiFi connection
            result = subprocess.run(['nmcli', '-t', '-f', 'ACTIVE,SSID', 'dev', 'wifi'], 
                                  capture_output=True, text=True)
            
            ssid = ''
            lines = result.stdout.strip().split('\n')
            for line in lines:
                if line.startswith('yes:'):
                    ssid = line.split(':', 1)[1]
                    break
            
            # Get IP address
            ip_address = ''
            if ssid:
                ip_result = subprocess.run(['hostname', '-I'], capture_output=True, text=True)
                ip_addresses = ip_result.stdout.strip().split()
                if ip_addresses:
                    ip_address = ip_addresses[0]  # Get first IP
            
            return {
                'ssid': ssid,
                'status': 'connected' if ssid else 'disconnected',
                'ip_address': ip_address,
                'success': True
            }
            
        except Exception as e:
            logger.error(f"Error getting WiFi status: {e}")
            return {
                'ssid': '',
                'status': 'error',
                'ip_address': '',
                'success': False,
                'error': str(e)
            }
    
    def scan_wifi_networks(self):
        """Scan for available WiFi networks"""
        try:
            # Rescan networks
            subprocess.run(['nmcli', 'dev', 'wifi', 'rescan'], capture_output=True)
            time.sleep(2)  # Wait for scan to complete
            
            # Get network list
            result = subprocess.run(['nmcli', '-t', '-f', 'SSID,SIGNAL,SECURITY', 'dev', 'wifi', 'list'],
                                  capture_output=True, text=True)
            
            networks = []
            seen_ssids = set()
            lines = result.stdout.strip().split('\n')
            
            for line in lines:
                if line and ':' in line:
                    parts = line.split(':', 2)
                    if len(parts) >= 3:
                        ssid = parts[0].strip()
                        signal = parts[1].strip()
                        security = parts[2].strip()
                        
                        if ssid and ssid not in seen_ssids and ssid != '--':
                            # Format: "SSID (Signal%, Security)"
                            security_text = security if security else "Open"
                            network_info = f"{ssid} ({signal}%, {security_text})"
                            networks.append(network_info)
                            seen_ssids.add(ssid)
            
            return {
                'networks': networks,
                'success': True
            }
            
        except Exception as e:
            logger.error(f"Error scanning WiFi: {e}")
            return {
                'networks': [],
                'success': False,
                'error': str(e)
            }
    
    def change_wifi_network(self, ssid, password):
        """Change WiFi network"""
        try:
            # First, try to connect to the network
            if password:
                cmd = ['nmcli', 'dev', 'wifi', 'connect', ssid, 'password', password]
            else:
                cmd = ['nmcli', 'dev', 'wifi', 'connect', ssid]
            
            result = subprocess.run(cmd, capture_output=True, text=True)
            
            if result.returncode == 0:
                return {
                    'success': True,
                    'message': f'Successfully connected to {ssid}'
                }
            else:
                return {
                    'success': False,
                    'message': f'Failed to connect: {result.stderr}'
                }
                
        except Exception as e:
            logger.error(f"Error changing WiFi: {e}")
            return {
                'success': False,
                'message': str(e)
            }

class WiFiHTTPHandler(BaseHTTPRequestHandler):
    def __init__(self, *args, wifi_manager=None, **kwargs):
        self.wifi_manager = wifi_manager
        super().__init__(*args, **kwargs)
    
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()
    
    def do_OPTIONS(self):
        self._set_headers()
    
    def do_GET(self):
        parsed_path = urlparse(self.path)
        
        if parsed_path.path == '/api/wifi/status':
            self._set_headers()
            status = self.wifi_manager.get_wifi_status()
            response = {
                'action': 'wifi_status',
                **status
            }
            self.wfile.write(json.dumps(response).encode())
        elif parsed_path.path == '/api/wifi/scan':
            self._set_headers()
            scan_result = self.wifi_manager.scan_wifi_networks()
            response = {
                'action': 'wifi_scan',
                **scan_result
            }
            self.wfile.write(json.dumps(response).encode())
        else:
            self.send_error(404, "Not Found")
    
    def do_POST(self):
        parsed_path = urlparse(self.path)
        
        if parsed_path.path == '/api/wifi/connect':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            
            try:
                data = json.loads(post_data)
                ssid = data.get('ssid', '')
                password = data.get('password', '')
                
                result = self.wifi_manager.change_wifi_network(ssid, password)
                
                self._set_headers()
                response = {
                    'action': 'wifi_changed',
                    **result
                }
                self.wfile.write(json.dumps(response).encode())
                
            except json.JSONDecodeError:
                self.send_error(400, "Invalid JSON")
        else:
            self.send_error(404, "Not Found")

class BluetoothServer:
    def __init__(self, wifi_manager):
        self.wifi_manager = wifi_manager
        self.server_sock = None
        self.running = False
    
    def start(self):
        """Start Bluetooth server"""
        try:
            self.server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
            self.server_sock.bind(("", bluetooth.PORT_ANY))
            self.server_sock.listen(1)
            
            port = self.server_sock.getsockname()[1]
            
            # Advertise service
            bluetooth.advertise_service(
                self.server_sock,
                "RobotWiFiService",
                service_id="94f39d29-7d6d-437d-973b-fba39e49d4ee",
                service_classes=[bluetooth.SERIAL_PORT_CLASS],
                profiles=[bluetooth.SERIAL_PORT_PROFILE]
            )
            
            logger.info(f"Bluetooth server listening on port {port}")
            self.running = True
            
            while self.running:
                try:
                    client_sock, client_info = self.server_sock.accept()
                    logger.info(f"Bluetooth client connected: {client_info}")
                    
                    # Handle client in separate thread
                    client_thread = threading.Thread(
                        target=self.handle_client,
                        args=(client_sock,)
                    )
                    client_thread.start()
                    
                except bluetooth.BluetoothError as e:
                    if self.running:
                        logger.error(f"Bluetooth error: {e}")
                        
        except Exception as e:
            logger.error(f"Failed to start Bluetooth server: {e}")
    
    def handle_client(self, client_sock):
        """Handle Bluetooth client connection"""
        try:
            while True:
                data = client_sock.recv(1024).decode('utf-8').strip()
                if not data:
                    break
                
                try:
                    command = json.loads(data)
                    response = self.process_command(command)
                    
                    client_sock.send((json.dumps(response) + '\n').encode('utf-8'))
                    
                except json.JSONDecodeError:
                    error_response = {'error': 'Invalid JSON'}
                    client_sock.send((json.dumps(error_response) + '\n').encode('utf-8'))
                    
        except Exception as e:
            logger.error(f"Error handling Bluetooth client: {e}")
        finally:
            client_sock.close()
            logger.info("Bluetooth client disconnected")
    
    def process_command(self, command):
        """Process command received via Bluetooth"""
        action = command.get('action', '')
        
        if action == 'get_wifi_status':
            status = self.wifi_manager.get_wifi_status()
            return {
                'action': 'wifi_status',
                **status
            }
        elif action == 'scan_wifi':
            scan_result = self.wifi_manager.scan_wifi_networks()
            return {
                'action': 'wifi_scan',
                **scan_result
            }
        elif action == 'change_wifi':
            data = command.get('data', {})
            ssid = data.get('ssid', '')
            password = data.get('password', '')
            
            result = self.wifi_manager.change_wifi_network(ssid, password)
            return {
                'action': 'wifi_changed',
                **result
            }
        else:
            return {'error': f'Unknown action: {action}'}
    
    def stop(self):
        """Stop Bluetooth server"""
        self.running = False
        if self.server_sock:
            self.server_sock.close()

def main():
    wifi_manager = WiFiManager()
    
    # Start HTTP server
    def http_server():
        handler = lambda *args, **kwargs: WiFiHTTPHandler(*args, wifi_manager=wifi_manager, **kwargs)
        httpd = HTTPServer(('0.0.0.0', 8080), handler)
        logger.info("HTTP server listening on port 8080")
        httpd.serve_forever()
    
    # Start Bluetooth server
    bluetooth_server = BluetoothServer(wifi_manager)
    
    # Start both servers in separate threads
    http_thread = threading.Thread(target=http_server)
    bluetooth_thread = threading.Thread(target=bluetooth_server.start)
    
    http_thread.daemon = True
    bluetooth_thread.daemon = True
    
    http_thread.start()
    bluetooth_thread.start()
    
    logger.info("Robot WiFi Management Server started")
    logger.info("HTTP API available at http://[robot_ip]:8080/api/")
    logger.info("Bluetooth service: RobotWiFiService")
    
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        logger.info("Stopping servers...")
        bluetooth_server.stop()

if __name__ == "__main__":
    main()