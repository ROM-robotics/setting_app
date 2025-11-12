# WiFi Manager - အမြန်လမ်းညွှန် (Quick Reference)

## 🚀 အရမ်းလွယ်ကူသော အဆင့် ၃ ဆင့်

### 1️⃣ Build & Run
```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build_desktop.sh
./build/Desktop-Debug/setting_app
```

### 2️⃣ Robot Server Run လုပ်ပါ (Robot Computer)
```bash
sudo python3 robot_server.py
```

### 3️⃣ WiFi ပြောင်းပါ
1. **"Refresh WiFi"** နှိပ်ပါ
2. **WiFi ရွေးပါ** (list ကနေ)
3. **Password ရိုက်ပါ** (လိုရင်)
4. ပြီးပါပြီ! ✅

---

## 🎨 UI Overview

```
┌─────────────────────────────────────────────────────┐
│  🟠 Robot WiFi Manager                           ●  │  ← Connection Status
├─────────────────────────────────────────────────────┤
│  [ Switch to Bluetooth Mode ]                       │  ← Mode Toggle
│  Current Mode: Ethernet                             │
├─────────────────────────────────────────────────────┤
│  Status: Connected            [Refresh WiFi]        │  ← Main Action
├─────────────────────────────────────────────────────┤
│  Current WiFi Network                               │
│  SSID: HomeWiFi                                    │
│  Status: connected                                 │  ← WiFi Info
│  IP Address: 192.168.1.150                        │
├─────────────────────────────────────────────────────┤
│  [14:30:45] WiFi Status refreshed                   │  ← Log
│  [14:30:46] Found 5 networks                       │
└─────────────────────────────────────────────────────┘
```

---

## 🔧 အခြေခံ လုပ်ဆောင်ချက်များ

### WiFi Scan & Connect
| လုပ်ဆောင်ချက် | နည်းလမ်း |
|--------------|--------|
| WiFi စာရင်း ကြည့်ရန် | "Refresh WiFi" နှိပ်ပါ |
| Network ရွေးရန် | Dialog ထဲက network ကို click |
| Password ထည့်ရန် | Password prompt မှာ ရိုက်ပါ |
| Cancel လုပ်ရန် | Dialog မှာ "Cancel" နှိပ်ပါ |

### Mode Switching
| Mode | အသုံးပြုနည်း |
|------|-----------|
| **Ethernet** | Robot နဲ့ တူညီတဲ့ network မှာ ရှိရမယ် |
| **Bluetooth** | Robot နဲ့ Bluetooth pair လုပ်ထားရမယ် |

### Connection Status
| Indicator | အဓိပ္ပါယ် |
|-----------|---------|
| 🟢 Green | Connected |
| 🔴 Red (တုန်) | Disconnected |

---

## 📡 WiFi Network Format

Dialog မှာ network format:
```
NetworkName (SignalStrength%, SecurityType)
```

**ဥပမာ:**
- `HomeWiFi (95%, WPA2)` = အရမ်းကောင်းတဲ့ signal, secured
- `Office_Guest (60%, Open)` = အလယ်အလတ် signal, password မလို
- `WeakNetwork (25%, WPA2)` = signal အားနည်းတယ်, secured

### Signal Strength Guide
- 🟢 **90-100%** = Excellent (အရမ်းကောင်းတယ်)
- 🟡 **70-89%** = Good (ကောင်းတယ်)
- 🟠 **50-69%** = Fair (အလယ်အလတ်)
- 🔴 **30-49%** = Weak (အားနည်းတယ်)
- ⚫ **0-29%** = Very Weak (အရမ်းအားနည်း)

---

## ⚡ လျင်မြန်သော Commands

### Robot Setup (One-time)
```bash
# Static IP သတ်မှတ်ရန်
sudo nmcli con modify "Wired connection 1" ipv4.addresses 192.168.1.100/24
sudo nmcli con modify "Wired connection 1" ipv4.method manual
sudo nmcli con up "Wired connection 1"

# Server run လုပ်ရန်
cd /path/to/project
sudo python3 robot_server.py
```

### Desktop App
```bash
# Build
./build_desktop.sh

# Run
./build/Desktop-Debug/setting_app

# Clean build
rm -rf build/Desktop-Debug
./build_desktop.sh
```

### Testing
```bash
# Mock test
python3 test_server.py

# HTTP test (robot running)
curl http://192.168.1.100:8080/api/wifi/status
curl http://192.168.1.100:8080/api/wifi/scan
```

---

## 🐛 အဖြစ်များသော ပြဿနာများ

### Connection Failed
**ပြဿနာ**: "Ethernet error: Connection refused"
- ✅ Robot server run နေသလား စစ်ပါ: `sudo python3 robot_server.py`
- ✅ IP address မှန်သလား စစ်ပါ: `ip addr show`
- ✅ Network ချိတ်ထားသလား စစ်ပါ: `ping 192.168.1.100`

### WiFi Scan Empty
**ပြဿနာ**: Dialog မှာ network တစ်ခုမှ မပေါ်ဘူး
- ✅ Robot မှာ WiFi adapter ရှိသလား: `nmcli dev wifi list`
- ✅ NetworkManager run နေသလား: `systemctl status NetworkManager`
- ✅ Rescan permission ရှိသလား: `sudo nmcli dev wifi rescan`

### Password Incorrect
**ပြဿနာ**: "Failed to connect: Secrets were required, but not provided"
- ✅ Password မှန်ကန်သလား ပြန်စစ်ပါ
- ✅ Network security type ကို စစ်ပါ (WPA2/WPA3)
- ✅ Robot ရဲ့ WiFi adapter မှာ WPA2 support ရှိသလား

### Bluetooth Not Working
**ပြဿနာ**: "Bluetooth error: Permission denied"
- ✅ Desktop: Bluetooth adapter ရှိသလား
- ✅ Robot: `sudo systemctl start bluetooth`
- ✅ Robot: `sudo hciconfig hci0 piscan`
- ✅ App ကို `sudo` နဲ့ run ကြည့်ပါ (testing အတွက်သာ)

---

## 📝 အရေးကြီးတဲ့ မှတ်ချက်များ

### Security
- 🔒 Production မှာ robot server ကို HTTPS သုံးပါ
- 🔒 WiFi passwords တွေကို secure storage မှာ သိမ်းပါ
- 🔒 Bluetooth pairing အတွက် PIN ထည့်ပါ
- 🔒 Open networks တွေမှာ သတိထားပါ

### Network
- 📡 Signal strength 70% အထက် ရှိရင် stable ဖြစ်မယ်
- 📡 5GHz band က 2.4GHz ထက် မြန်ပေမယ့် range တို
- 📡 Ethernet က Bluetooth ထက် မြန်ပြီး reliable
- 📡 Robot ကို static IP သတ်မှတ်ထားရင် ပိုကောင်းတယ်

### Tips
- 💡 WiFi ပြောင်းမယ်ဆိုရင် signal strength မြင့်တာ ရွေးပါ
- 💡 Robot server ကို systemd service အဖြစ် setup လုပ်ပါ
- 💡 Desktop app ကို Ethernet mode နဲ့ စမ်းပါ (လွယ်တယ်)
- 💡 Password မှားရင် 3 ကြိမ် အထိ ထပ်စမ်းကြည့်နိုင်တယ်

---

## 📚 နောက်ထပ် အကူအညီ

### Documentation Files
- `DESKTOP_USAGE_MM.md` - အသေးစိတ် လမ်းညွှန် (Myanmar)
- `DESKTOP_USAGE.md` - Detailed guide (English)
- `WIFI_SCAN_IMPLEMENTATION.md` - Technical details
- `README.md` - Project overview

### Test Files
- `test_server.py` - Mock WiFi testing
- `robot_server.py` - Production server

### Build Files
- `build_desktop.sh` - Desktop build script
- `CMakeLists.txt` - CMake configuration

---

## 🎯 Quick Troubleshooting Checklist

အဆင့်လိုက် စစ်ဆေးပါ:

- [ ] Robot server run နေသလား? (`sudo python3 robot_server.py`)
- [ ] Desktop နဲ့ Robot တူညီတဲ့ network မှာ ရှိသလား?
- [ ] IP address မှန်သလား? (`192.168.1.100`)
- [ ] App ကို build ပြီးပြီလား? (`./build_desktop.sh`)
- [ ] Ethernet mode ကနေ စမ်းထားပြီးပြီလား?
- [ ] WiFi adapter ရှိသလား? (`nmcli dev status`)
- [ ] NetworkManager run နေသလား? (`systemctl status NetworkManager`)

အားလုံး ✅ ဖြစ်ရင် အလုပ်လုပ်ရပါမယ်! 🎉

---

**Version**: 1.0.0 (Desktop Build with WiFi Scan Dialog)  
**Last Updated**: 2024  
**Platform**: Linux Desktop (Ubuntu/Debian)  
**Qt Version**: 6.8.3
