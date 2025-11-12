# Robot WiFi Management App - မြန်မာလို လမ်းညွှန်

## အက်ပ်ရဲ့ အင်္ဂါရပ်များ

- **Ethernet နဲ့ Bluetooth နှစ်မျိုးလုံး သုံးနိုင်**: Robot ကို Ethernet cable နဲ့ချိတ်ရင် Ethernet mode သုံးပါ။ Bluetooth နဲ့ချိတ်ရင် Bluetooth mode သုံးပါ။
- **WiFi Status ကြည့်ရှုခြင်း**: Robot computer ရဲ့ လက်ရှိချိတ်ထားတဲ့ WiFi network ကို ကြည့်နိုင်ပါတယ်
- **WiFi ပြောင်းခြင်း**: Robot ကို အခြား WiFi network ကို ချိတ်ပေးနိုင်ပါတယ်
- **Virtual Keyboard**: စာရိုက်ဖို့ screen ပေါ်မှာ keyboard ပေါ်လာပါတယ်
- **လှပတဲ့ UI**: လိမ္မော်ရောင် gradient design နဲ့ ဒီဇိုင်းလုပ်ထားပါတယ်

## လိုအပ်တာတွေ

### Android Device
- Android 6.0 (API 23) သို့မဟုတ် ပိုမြင့်တဲ့ ဗားရှင်း
- Bluetooth ပါရမယ်
- WiFi ရှိရမယ်

### Robot Computer (Ubuntu 22.04)
- Static IP Address သတ်မှတ်ထားရမယ် (Ethernet mode အတွက်)
- Bluetooth enable လုပ်ထားရမယ်
- Python 3 နဲ့ Server script run ထားရမယ်

## Installation လမ်းညွှန်

### Robot Computer မှာ Setup လုပ်ခြင်း

#### 1. လိုအပ်တဲ့ Package တွေ Install လုပ်ပါ
```bash
sudo apt update
sudo apt install python3 python3-pip network-manager bluetooth bluez
pip3 install pybluez
```

#### 2. Ethernet အတွက် Static IP သတ်မှတ်ပါ
```bash
# Network connection ကို edit လုပ်ပါ (IP: 192.168.1.100)
sudo nmcli con modify "Ethernet Connection" ipv4.addresses 192.168.1.100/24
sudo nmcli con modify "Ethernet Connection" ipv4.method manual
sudo nmcli con up "Ethernet Connection"
```

#### 3. Bluetooth ကို enable လုပ်ပါ
```bash
sudo systemctl enable bluetooth
sudo systemctl start bluetooth
sudo hciconfig hci0 up
sudo hciconfig hci0 piscan
```

#### 4. Server Script ကို run ပါ
```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
chmod +x robot_server.py
sudo python3 robot_server.py
```

Server စတင်ပြီဆိုရင်:
- HTTP API: port 8080 မှာ run နေပါမယ်
- Bluetooth Service: "RobotWiFiService" အမည်နဲ့ အဆင်သင့်ဖြစ်ပါမယ်

### Android App Build လုပ်ခြင်း

#### Qt Creator သုံးပြီး Build လုပ်ပါ
1. Qt Creator ကို ဖွင့်ပါ
2. `CMakeLists.txt` ကို Open လုပ်ပါ
3. Android kit (arm64-v8a) ကို ရွေးပါ
4. Configure ကို နှိပ်ပါ
5. Build နဲ့ Deploy ကို လုပ်ပါ

## အသုံးပြုနည်း

### 1. App ကို ဖွင့်ပါ
Android device မှာ "Robot WiFi Manager" ကို ဖွင့်ပါ

### 2. Robot နဲ့ ချိတ်ဆက်ပါ

#### Ethernet Mode (Default)
- Robot computer နဲ့ Android device ကို တူညီတဲ့ network မှာ ရှိအောင်လုပ်ပါ
- "Connect" button ကို နှိပ်ပါ
- Connection indicator (●) က စိမ်းရောင်ဖြစ်ရင် ချိတ်ဆက်ပြီးပါပြီ

#### Bluetooth Mode
- "Switch to Bluetooth Mode" button ကို နှိပ်ပါ
- App က robot device ကို အလိုအလျောက် ရှာပါမယ်
- "Connect" button ကို နှိပ်ပါ

### 3. WiFi Status ကြည့်ပါ
- "Refresh WiFi" button ကို နှိပ်ပါ
- လက်ရှိ WiFi SSID နဲ့ connection status ကို မြင်ရပါမယ်

### 4. WiFi Network ပြောင်းပါ

1. "Enter new WiFi SSID" text field ကို နှိပ်ပါ
2. Virtual keyboard ပေါ်လာပါမယ်
3. WiFi network name (SSID) ကို ရိုက်ပါ
4. Password field မှာ WiFi password ကို ရိုက်ပါ (password မလိုရင် ကွက်လပ်ထားလို့ရပါတယ်)
5. "Change WiFi Network" button ကို နှိပ်ပါ
6. Status message တွေမှာ progress ကို မြင်ရပါမယ်

### 5. Virtual Keyboard အသုံးပြုနည်း

- **စာလုံးတွေ**: QWERTY keyboard layout အတိုင်း ရိုက်နိုင်ပါတယ်
- **နံပါတ်တွေ**: အပေါ်ဆုံး row မှာ 0-9 ရှိပါတယ်
- **Space**: Space bar နှိပ်ပါ
- **Back**: နောက်ဆုံး character ကို ဖျက်ပါတယ်
- **Done**: Keyboard ကို ပိတ်ပါတယ်

## Mode နှစ်မျိုး ကွာခြားချက်

### Ethernet Mode
- **အားသာချက်**: တည်ငြိမ်ပြီး မြန်ဆန်ပါတယ်
- **လိုအပ်ချက်**: Robot နဲ့ Android device ကို တူညီတဲ့ network မှာ ရှိရမယ်
- **Static IP**: 192.168.1.100 (default)
- **Port**: 8080

### Bluetooth Mode
- **အားသာချက်**: Cable မလိုပါဘူး၊ wireless ဖြစ်ပါတယ်
- **လိုအပ်ချက်**: နှစ်ခုလုံးမှာ Bluetooth ရှိရမယ်
- **Range**: 10-30 meters ခန့်
- **Auto-discovery**: App က robot device ကို အလိုအလျောက် ရှာပါတယ်

## အဖြစ်များတဲ့ ပြဿနာတွေ

### Ethernet နဲ့ မချိတ်နိုင်ဘူး
1. Robot IP address ကို စစ်ပါ: `ip addr show`
2. Server run နေလား စစ်ပါ: `sudo netstat -tlnp | grep 8080`
3. Android နဲ့ Robot တူညီတဲ့ network မှာ ရှိလား စစ်ပါ
4. Firewall ကို စစ်ပါ: `sudo ufw status`

### Bluetooth နဲ့ မချိတ်နိုင်ဘူး
1. နှစ်ခုလုံးမှာ Bluetooth on ဖွင့်ထားလား စစ်ပါ
2. Robot မှာ Bluetooth service run နေလား စစ်ပါ: `sudo systemctl status bluetooth`
3. Android app မှာ Bluetooth permission ပေးထားလား စစ်ပါ
4. Robot ကို discoverable mode ထားပါ: `sudo hciconfig hci0 piscan`

### WiFi မပြောင်းနိုင်ဘူး
1. Robot မှာ NetworkManager run နေလား စစ်ပါ: `systemctl status NetworkManager`
2. WiFi adapter ရှိလား စစ်ပါ: `nmcli device status`
3. Server ကို sudo နဲ့ run ထားလား စစ်ပါ
4. SSID နဲ့ password မှန်ကန်လား စစ်ပါ

### Virtual keyboard မပေါ်ဘူး
1. Text field ကို တိုက်ရိုက် နှိပ်ပါ
2. Screen ကို အောက်ဆုံး scroll လုပ်ကြည့်ပါ
3. App ကို ပိတ်ပြီး ပြန်ဖွင့်ကြည့်ပါ

## အရေးကြီးတဲ့ မှတ်ချက်များ

1. **Security**: Production အတွက် သုံးမယ်ဆိုရင် authentication နဲ့ encryption ထည့်သင့်ပါတယ်
2. **IP Configuration**: Robot IP address ကို လိုအပ်သလို ပြောင်းလို့ရပါတယ် (`networkmanager.cpp` မှာ)
3. **Bluetooth Pairing**: ပထမဆုံး connect လုပ်တဲ့အခါ pairing လုပ်ဖို့ လိုပါမယ်
4. **Permissions**: Android 12+ မှာ Bluetooth permission တွေ ခွင့်ပြုပေးဖို့ လိုပါမယ်

## ထပ်ဆောင်း အချက်အလက်

အသေးစိတ် technical documentation အတွက် `README.md` ကို ဖတ်ပါ။

## Credits

Qt 6.8.3 နဲ့ CMake သုံးပြီး ဖန်တီးထားပါတယ်။