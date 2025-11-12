# Robot WiFi Manager - Desktop အသုံးပြုနည်း လမ်းညွှန်

## 🆕 အသစ်ပြောင်းလဲမှုများ (Latest Update)

### WiFi Selection Dialog Feature
- **လွယ်ကူသော WiFi ရွေးချယ်မှု**: "Refresh WiFi" button နှိပ်ရုံနဲ့ available networks တွေကို dialog box မှာ မြင်ရပါပြီ
- **Signal Strength Display**: WiFi signal အား percentage နဲ့ ပြပေးပါတယ်
- **Security Type**: WPA2, Open စတဲ့ security type တွေ ပြပေးပါတယ်
- **IP Address Display**: လက်ရှိ WiFi connection ရဲ့ IP address ကို ပြပေးပါတယ်
- **Simple Workflow**: Manual SSID ရိုက်စရာ မလို၊ list ကနေ ရွေးရုံပါပဲ

### UI ပိုမို ရိုးရှင်းလာပါပြီ
- ✅ WiFi change form ဖယ်ရှားလိုက်ပါပြီ (manual SSID entry)
- ✅ Dialog-based selection ပိုလွယ်ကူပါတယ်
- ✅ IP address ပြပေးပါပြီ
- ✅ Landscape mode (1200x600) အတွက် optimize လုပ်ထားပါတယ်

---

## အမြန် စတင်ခြင်း

### 1. Build လုပ်ခြင်း (Linux Desktop)

#### လိုအပ်တာများ
- Qt 6.8.3 (Desktop version)
- CMake 3.19+
- C++ compiler (g++)
- Linux (Ubuntu/Debian tested)

#### Build လုပ်နည်း

**နည်းလမ်း ၁ - Build Script သုံးခြင်း (လွယ်ကူဆုံး):**

```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build_desktop.sh
```

Build ပြီးရင်:
```bash
./build/Desktop-Debug/setting_app
```

**နည်းလမ်း ၂ - Manual Build:**

```bash
# Build directory ဖန်တီးပါ
mkdir -p build/Desktop-Debug
cd build/Desktop-Debug

# CMake configure လုပ်ပါ
cmake -DCMAKE_BUILD_TYPE=Debug ../..

# Build လုပ်ပါ
cmake --build . --parallel $(nproc)

# Run လုပ်ပါ
./setting_app
```

**နည်းလမ်း ၃ - Qt Creator သုံးခြင်း:**

1. Qt Creator ကို ဖွင့်ပါ
2. File → Open File or Project
3. `CMakeLists.txt` ကို ရွေးပါ
4. Desktop Qt 6.8.3 kit ကို ရွေးပါ
5. Configure Project ကို နှိပ်ပါ
6. Build (Ctrl+B) ပြီး Run (Ctrl+R) လုပ်ပါ

---

## Application ကို စတင်အသုံးပြုခြင်း

### မျက်နှာပြင် သိရှိရန်

App ကို ဖွင့်လိုက်ရင် အောက်ပါ အစိတ်အပိုင်းတွေ မြင်ရပါမယ်:

```
┌────────────────────────────────────────────────┐
│  🟠 Robot WiFi Manager                     ●  │  ← Header (Connection Indicator)
├────────────────────────────────────────────────┤
│  [ Switch to Bluetooth Mode ]                 │  ← Mode Toggle Button
│  Current Mode: Ethernet                        │
├────────────────────────────────────────────────┤
│  Status: Disconnected       [Refresh WiFi]     │  ← Connection Controls
├────────────────────────────────────────────────┤
│  Current WiFi Network                          │
│  SSID: Not Connected                          │  ← WiFi Info Display
│  Status: Unknown                              │
│  IP Address: N/A                              │
├────────────────────────────────────────────────┤
│  Status messages will appear here...          │  ← Log Area
│                                                │
└────────────────────────────────────────────────┘
```

**အဓိက အစိတ်အပိုင်းများ:**

1. **Header Bar** (အပေါ်ဆုံး):
   - Orange gradient background
   - "Robot WiFi Manager" title
   - Connection indicator (● - ချိတ်ဆက်မှု အခြေအနေ)

2. **Mode Selection** (အပေါ်ပိုင်း):
   - Mode toggle button - Ethernet/Bluetooth ကြား ပြောင်းဖို့
   - Current mode display - လက်ရှိ အသုံးပြုနေတဲ့ connection mode

3. **Connection Controls** (အလယ်အလတ်):
   - **Refresh WiFi button** - WiFi network များကို scan လုပ်ပြီး ရွေးချယ်ခြင်း
   - Connection status - လက်ရှိ ချိတ်ဆက်မှု အခြေအနေ

4. **WiFi Information Display**:
   - **SSID** - လက်ရှိ ချိတ်ဆက်ထားတဲ့ WiFi network နာမည်
   - **Status** - Connected/Disconnected/Connecting
   - **IP Address** - Robot ရဲ့ လက်ရှိ IP address (ချိတ်ဆက်ထားရင်)

5. **Log Area** (အောက်ပိုင်း):
   - Status messages
   - Error notifications
   - Connection logs
└────────────────────────────────────────────────┘
```

### အစိတ်အပိုင်းတွေ ရှင်းလင်းချက်

#### 1. **Header Section**
- **Title**: Robot WiFi Manager
- **Connection Indicator** (●): 
  - 🔴 Red (တုန်ခါနေတယ်) = Disconnected
  - 🟢 Green (ရပ်နေတယ်) = Connected

#### 2. **Mode Selection**
- **Toggle Button**: Ethernet ⇄ Bluetooth ပြောင်းဖို့
- **Mode Label**: လက်ရှိ mode ပြပေးတယ်

#### 3. **Connection Controls**
- **Status Label**: Connection အခြေအနေ
- **Connect Button**: ချိတ်/ဖြုတ် ခလုတ်
- **Refresh WiFi**: WiFi status ကို refresh လုပ်တာ

#### 4. **WiFi Information**
- **SSID**: လက်ရှိချိတ်ထားတဲ့ WiFi network name
- **Status**: Connection အခြေအနေ (connected/disconnected/error)

#### 5. **WiFi Change Form**
- **SSID Input**: အသစ် WiFi network name ရိုက်ရန်
- **Password Input**: WiFi password ရိုက်ရန်
- **Change Button**: WiFi network ပြောင်းရန်

#### 6. **Status Log**
- Timestamped messages
- Green = Success
- Red = Error
- Auto-scroll to bottom

---

## အသုံးပြုနည်း - ခြေလှမ်းအလိုက်

### Setup 1: Robot Computer ပြင်ဆင်ခြင်း

Desktop application က robot computer ကို ချိတ်ဆက်ဖို့ လိုတယ်။ Robot ပေါ်မှာ server run ထားရမယ်။

#### Ubuntu 22.04 Robot Computer မှာ:

```bash
# 1. လိုအပ်တာတွေ install လုပ်ပါ
sudo apt update
sudo apt install python3 python3-pip network-manager bluetooth bluez
pip3 install pybluez

# 2. Ethernet အတွက် Static IP သတ်မှတ်ပါ
sudo nmcli con modify "Wired connection 1" ipv4.addresses 192.168.1.100/24
sudo nmcli con modify "Wired connection 1" ipv4.method manual
sudo nmcli con up "Wired connection 1"

# သို့မဟုတ် သင့် computer ရဲ့ existing IP ကို သုံးလို့ရပါတယ်
ip addr show  # IP address ကို ကြည့်ပါ

# 3. Server ကို run ပါ
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
sudo python3 robot_server.py
```

Server run နေရင်:
```
INFO:__main__:HTTP server listening on port 8080
INFO:__main__:Bluetooth server listening on port 1
INFO:__main__:Robot WiFi Management Server started
INFO:__main__:HTTP API available at http://[robot_ip]:8080/api/
INFO:__main__:Bluetooth service: RobotWiFiService
```

### Setup 2: Desktop Application Configuration

Robot IP address သတ်မှတ်ရန် (လိုအပ်ရင်):

`networkmanager.cpp` ကို edit လုပ်ပါ (line 14 ဝန်းကျင်):

```cpp
NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_robotIpAddress("192.168.1.100") // ← ဒီမှာ robot IP ကို ပြောင်းပါ
    , m_robotPort(8080)
```

သို့မဟုတ် သင့် robot ရဲ့ actual IP ကို သုံးပါ:
```cpp
m_robotIpAddress("192.168.1.50") // သင့် robot IP
```

ပြောင်းပြီးရင် rebuild လုပ်ပါ:
```bash
./build_desktop.sh
```

---

## အသုံးပြုခြင်း - Ethernet Mode

### အဆင့် ၁: Application ကို စတင်ပါ

```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build/Desktop-Debug/setting_app
```

### အဆင့် ၂: Robot နဲ့ ချိတ်ဆက်ပါ

1. **သေချာပါစေ**: Desktop computer နဲ့ robot computer တူညီတဲ့ network မှာ ရှိရမယ်
   - တူညီတဲ့ WiFi network မှာ ရှိရမယ်
   - သို့မဟုတ် Ethernet cable နဲ့ တိုက်ရိုက်ချိတ်ထားရမယ်

2. **Connection indicator** ကို ကြည့်ပါ:
   - 🔴 Red တုန်ခါနေရင် = Not connected yet

3. **"Connect" button** ကို နှိပ်ပါ

4. အောင်မြင်ရင်:
   - Status: **"Status: Connected"** ဖြစ်သွားမယ်
   - Indicator: **🟢 Green** အဖြစ် ပြောင်းမယ်
   - Log area မှာ: `[timestamp] Connected to robot successfully`
   - Automatic WiFi status refresh လုပ်မယ်

5. မအောင်မြင်ရင်:
   - Error message မြင်ရမယ်: `"Ethernet error: ..."`
   - အကြောင်းရင်းများ:
     - Robot server မ run ထားဘူး
     - IP address မှားနေတယ်
     - Network ချိတ်မထားဘူး

### အဆင့် ၃: WiFi Status ကြည့်ပါ

Connected ဖြစ်ပြီဆိုရင် automatic ရတယ်။ သို့မဟုတ်:

1. **"Refresh WiFi" button** ကို နှိပ်ပါ

2. WiFi Scan Dialog တက်လာမယ်:
   ```
   ┌─────────────────────────────────────┐
   │  Available WiFi Networks           │
   ├─────────────────────────────────────┤
   │  • HomeWiFi (95%, WPA2)            │
   │  • Office_5G (85%, WPA2)           │
   │  • CafeNetwork (70%, Open)         │
   │  • GuestNetwork (60%, WPA2)        │
   │  • WeakSignal (30%, WPA2)          │
   ├─────────────────────────────────────┤
   │         [ Connect ]  [ Cancel ]     │
   └─────────────────────────────────────┘
   ```

3. လက်ရှိ WiFi info မြင်ရမယ်:
   ```
   Current WiFi Network
   SSID: HomeWiFi
   Status: connected
   IP Address: 192.168.1.150
   ```

4. Log area မှာ:
   ```
   [14:30:45] Scanning WiFi networks...
   [14:30:47] Found 5 WiFi networks
   [14:30:47] WiFi Status - SSID: HomeWiFi, Status: connected, IP: 192.168.1.150
   ```

### အဆင့် ၄: WiFi Network ပြောင်းပါ

1. **"Refresh WiFi" button** ကို နှိပ်ပြီး WiFi scan dialog ကို ဖွင့်ပါ

2. **ရွေးချယ်ပါ**: List ထဲက WiFi network တစ်ခု ကို click လုပ်ပါ
   - Network info format: `SSID (Signal%, Security)`
   - Signal strength ကြည့်ပြီး ရွေးပါ (percentage မြင့်တာ ကောင်းတယ်)
   - Security type: WPA2 (secured), Open (password မလို)

3. **"Connect" button** ကို နှိပ်ပါ

4. **Password prompt** ပေါ်လာမယ် (secured network ဆိုရင်):
   ```
   ┌─────────────────────────────────────┐
   │  Enter WiFi Password               │
   │  ┌─────────────────────────────┐   │
   │  │ ••••••••••                  │   │
   │  └─────────────────────────────┘   │
   │         [ OK ]  [ Cancel ]          │
   └─────────────────────────────────────┘
   ```
   
   **မှတ်ချက်**: 
   - Open network (password မလို) ဆိုရင် password prompt မပေါ်ဘူး
   - Password မှားရင် connection failed ဖြစ်မယ်

5. **Password ရိုက်ပြီး OK နှိပ်ပါ**

6. Status messages:
   ```
   [14:35:10] Connecting to: Office_5G
   [14:35:15] WiFi changed successfully: Successfully connected to Office_5G
   [14:35:17] Refreshing WiFi status...
   [14:35:18] WiFi Status - SSID: Office_5G, Status: connected, IP: 192.168.1.175
   ```

7. Dialog ပိတ်သွားပြီး auto-refresh လုပ်မယ်

### WiFi Selection Dialog အသုံးပြုနည်း

**Network List Format:**
```
NetworkName (SignalStrength%, SecurityType)
```

**Signal Strength အဓိပ္ပါယ်:**
- 90-100% = အရမ်းကောင်းတယ် (Excellent)
- 70-89% = ကောင်းတယ် (Good)
- 50-69% = အလယ်အလတ် (Fair)
- 30-49% = အားနည်းတယ် (Weak)
- 0-29% = အရမ်းအားနည်းတယ် (Very weak)

**Security Types:**
- WPA2 = Password လို (secured network)
- Open = Password မလို (public/guest network)
- WPA3 = New security standard (password လို)

**Tips:**
- Signal strength မြင့်တဲ့ network ကို ရွေးပါ
- Public WiFi တွေမှာ secured connection သုံးပါ
- Connection မအောင်မြင်ရင် password ပြန်စစ်ပါ

### အဆင့် ၅: Disconnect လုပ်ပါ (လိုရင်)

Mode toggle button နဲ့ Ethernet mode ကို ပြန်ပြောင်းပြီး disconnect လုပ်နိုင်ပါတယ်။

---

## အသုံးပြုခြင်း - Bluetooth Mode

### အဆင့် ၁: Bluetooth Mode ကို ပြောင်းပါ

1. **"Switch to Bluetooth Mode" button** ကို နှိပ်ပါ

2. Mode label ပြောင်းမယ်:
   ```
   Current Mode: Bluetooth
   ```

3. Button text ပြောင်းမယ်:
   ```
   [ Switch to Ethernet Mode ]
   ```

4. Log message:
   ```
   [14:40:00] Switched to Bluetooth mode
   ```

### အဆင့် ၂: Bluetooth Setup (Robot)

Robot computer မှာ Bluetooth enable လုပ်ထားဖို့:

```bash
# Bluetooth service start လုပ်ပါ
sudo systemctl start bluetooth

# Bluetooth discoverable လုပ်ပါ
sudo hciconfig hci0 up
sudo hciconfig hci0 piscan

# Check status
hciconfig hci0
```

### အဆင့် ၃: Connect via Bluetooth

1. **"Connect" button** ကို နှိပ်ပါ

2. App က robot device ကို အလိုအလျောက် ရှာပါမယ်:
   ```
   [14:42:00] Connecting...
   [14:42:03] Starting Bluetooth device discovery...
   [14:42:10] Found robot device: ubuntu
   [14:42:12] Bluetooth connected
   [14:42:12] Connected to robot successfully
   ```

3. ပထမဆုံး connect လုပ်တဲ့အခါ pairing လုပ်ဖို့ လိုနိုင်ပါတယ်

4. Connected ဖြစ်ပြီဆိုရင် WiFi operations တွေ အတူတူပဲ လုပ်လို့ရပါပြီ

---

## Virtual Keyboard အသုံးပြုခြင်း

Desktop version မှာ virtual keyboard ကို text field တွေမှာ focus လုပ်ရင် ပေါ်လာပါမယ်။

### Keyboard Layout

```
┌─────────────────────────────────────────────┐
│  [ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ][ 8 ]...│
│  [ Q ][ W ][ E ][ R ][ T ][ Y ][ U ][ I ]...│
│  [ A ][ S ][ D ][ F ][ G ][ H ][ J ][ K ]...│
│    [ Z ][ X ][ C ][ V ][ B ][ N ][ M ]...   │
│  [ Back ]  [   Space   ]  [ Done ] [ . ][-] │
└─────────────────────────────────────────────┘
```

### Keys အလုပ်လုပ်ပုံ

- **Letters & Numbers**: စာလုံးတွေ ထည့်တာ
- **Space**: Space bar
- **Back**: နောက်ဆုံး character ဖျက်တာ
- **Done**: Keyboard ပိတ်တာ
- **.** & **-**: Special characters for WiFi names

### အသုံးပြုနည်း

1. SSID input field ကို click လုပ်ပါ
2. Keyboard အောက်မှာ ပေါ်လာမယ်
3. WiFi name ရိုက်ပါ: `Office-WiFi-5G`
4. **Done** နှိပ်ပါ
5. Password field ကို click လုပ်ပြီး password ရိုက်ပါ
6. **Done** နှိပ်ပါ
7. **Change WiFi Network** button နှိပ်ပါ

---

## အဖြစ်များတဲ့ ပြဿနာများနဲ့ ဖြေရှင်းနည်းများ

### ပြဿနာ ၁: Build မအောင်မြင်ဘူး

**Symptoms:**
```
CMake Error: Qt6 not found
```

**ဖြေရှင်းနည်း:**
```bash
# Qt PATH ကို သတ်မှတ်ပါ
export PATH=~/Qt/6.8.3/gcc_64/bin:$PATH
export CMAKE_PREFIX_PATH=~/Qt/6.8.3/gcc_64

# ပြန် build လုပ်ပါ
./build_desktop.sh
```

### ပြဿနာ ၂: "Ethernet error: Connection refused"

**အကြောင်းရင်း:**
- Robot server မ run ထားဘူး
- IP address မှားနေတယ်
- Firewall block လုပ်နေတယ်

**ဖြေရှင်းနည်း:**

```bash
# Robot မှာ server run ထားလား စစ်ပါ
ps aux | grep robot_server.py

# မရှိရင် run ပါ
sudo python3 robot_server.py

# Port ဖွင့်ထားလား စစ်ပါ
sudo netstat -tlnp | grep 8080

# Desktop ကနေ test လုပ်ပါ
curl http://192.168.1.100:8080/api/wifi/status
```

### ပြဿနာ ၃: "Bluetooth not connected"

**ဖြေရှင်းနည်း:**

```bash
# Robot မှာ Bluetooth service စစ်ပါ
sudo systemctl status bluetooth

# မ run ထားရင် start လုပ်ပါ
sudo systemctl start bluetooth

# Discoverable လုပ်ပါ
sudo hciconfig hci0 piscan

# Desktop ကနေ scan လုပ်ကြည့်ပါ
bluetoothctl
> scan on
> devices
```

### ပြဿနာ ၄: WiFi မပြောင်းနိုင်ဘူး

**Symptoms:**
```
WiFi change failed: Error: command failed
```

**ဖြေရှင်းနည်း:**

```bash
# Robot မှာ NetworkManager run နေလား စစ်ပါ
systemctl status NetworkManager

# WiFi adapter ရှိလား စစ်ပါ
nmcli device status

# Manual test လုပ်ပါ
nmcli dev wifi connect "TestNetwork" password "testpass"

# Server ကို sudo နဲ့ run ထားဖို့ မမေ့ပါနဲ့
sudo python3 robot_server.py
```

### ပြဿနာ ၅: Application ပြတ်သွားတယ် (Crash)

**Debug လုပ်နည်း:**

```bash
# Debug mode နဲ့ run ပါ
QT_DEBUG_PLUGINS=1 ./build/Desktop-Debug/setting_app

# Log တွေကို ကြည့်ပါ
QT_LOGGING_RULES="*.debug=true" ./build/Desktop-Debug/setting_app

# Core dump enable လုပ်ပါ
ulimit -c unlimited
./build/Desktop-Debug/setting_app
```

### ပြဿနာ ၆: Virtual Keyboard မပေါ်ဘူး

**ဖြေရှင်းနည်း:**
1. Input field ကို တိုက်ရိုက် click လုပ်ပါ
2. Screen ကို အောက်ဆုံး scroll လုပ်ကြည့်ပါ
3. Window size ကို ကြီးအောင် လုပ်ကြည့်ပါ

---

## Advanced အသုံးပြုမှုများ

### Configuration ပြောင်းခြင်း

#### Robot IP Address ပြောင်းခြင်း

`networkmanager.cpp` ကို edit လုပ်ပါ:

```cpp
// Line 14 ဝန်းကျင်
NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_robotIpAddress("192.168.1.100") // ← ဒီမှာ ပြောင်းပါ
    , m_robotPort(8080)
```

#### Port Number ပြောင်းခြင်း

```cpp
m_robotPort(8080) // Default port
// ပြောင်းမယ်ဆိုရင်:
m_robotPort(9090) // New port
```

Robot server မှာလဲ ပြောင်းရမယ်:

`robot_server.py`:
```python
# Line 250 ဝန်းကျင်
httpd = HTTPServer(('0.0.0.0', 8080), handler)
# ပြောင်းမယ်ဆိုရင်:
httpd = HTTPServer(('0.0.0.0', 9090), handler)
```

#### Bluetooth Device Name ပြောင်းခြင်း

`networkmanager.cpp` line 199 ဝန်းကျင်:

```cpp
if (device.name().contains("robot", Qt::CaseInsensitive) || 
    device.name().contains("ubuntu", Qt::CaseInsensitive)) {
    // ပြောင်းမယ်ဆိုရင်:
    if (device.name().contains("myrobot", Qt::CaseInsensitive)) {
```

### Connection Timeout ပြောင်းခြင်း

`networkmanager.cpp` line 50 ဝန်းကျင်:

```cpp
m_connectionTimer->start(5000); // 5 seconds
// ပြောင်းမယ်ဆိုရင်:
m_connectionTimer->start(10000); // 10 seconds
```

---

## Testing လုပ်နည်း

### Unit Testing

```bash
# Build with tests
cd build/Desktop-Debug
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON ../..
cmake --build .

# Run tests
ctest --output-on-failure
```

### Manual Testing Checklist

- [ ] Application launch ဖြစ်လား
- [ ] UI render correct ဖြစ်လား (orange gradient)
- [ ] Connection indicator animate ဖြစ်လား
- [ ] Ethernet mode connect လုပ်လို့ရလား
- [ ] WiFi status refresh ဖြစ်လား
- [ ] WiFi network change လုပ်လို့ရလား
- [ ] Mode switch (Ethernet ⇄ Bluetooth) လုပ်လို့ရလား
- [ ] Bluetooth mode connect လုပ်လို့ရလား
- [ ] Virtual keyboard ပေါ်လား
- [ ] Status messages ပြလား
- [ ] Error handling အလုပ်လုပ်လား

### Integration Testing

Robot server နဲ့ ချိတ်ပြီး test:

```bash
# Terminal 1: Robot server
cd /path/to/setting_app
sudo python3 robot_server.py

# Terminal 2: Desktop app
./build/Desktop-Debug/setting_app

# Terminal 3: Monitor logs
tail -f /var/log/syslog | grep -i wifi
```

---

## Performance Tips

1. **Release Build** အတွက်:
   ```bash
   mkdir -p build/Desktop-Release
   cd build/Desktop-Release
   cmake -DCMAKE_BUILD_TYPE=Release ../..
   cmake --build .
   ./setting_app
   ```

2. **Memory Usage** လျှော့ချဖို့:
   - Connection timer interval တိုးပါ
   - Log size limit လုပ်ပါ

3. **Network Performance** မြှင့်တင်ဖို့:
   - HTTP keepalive သုံးပါ
   - Timeout values adjust လုပ်ပါ

---

## နောက်ထပ် အချက်အလက်များ

### Log Files တွေ

Application logs:
```bash
# stdout/stderr
./setting_app 2>&1 | tee app.log

# Qt debug output
QT_LOGGING_RULES="*.debug=true" ./setting_app
```

Robot server logs:
```bash
# Run with logging
sudo python3 robot_server.py 2>&1 | tee server.log
```

### Keyboard Shortcuts

Desktop version မှာ:
- **Ctrl+Q**: Quit application
- **F11**: Fullscreen toggle (if supported)
- **Escape**: Close virtual keyboard

---

## Support နဲ့ Documentation

- **Technical Documentation**: `README.md`
- **Architecture**: `ARCHITECTURE.md`
- **Qt Creator Setup**: `QT_CREATOR_SETUP.md`
- **Quick Start**: `QUICKSTART.md`

---

## နိဂုံး

Desktop version က development နဲ့ testing အတွက် အဆင်ပြေပါတယ်။ UI နဲ့ functionality တွေကို အလွယ်တကူ test လုပ်နိုင်ပါတယ်။

ပြီးရင် Android version build ဖို့ `QT_CREATOR_SETUP.md` ကို ကြည့်ပါ။

**Happy Testing!** 🚀