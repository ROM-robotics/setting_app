# Robot WiFi Manager - Desktop Version အသုံးပြုနည်း

## ✅ Build ပြီးပြီ!

Application ကို build လုပ်ပြီးပါပြီ။ အခု run လို့ရပါပြီ။

## 🚀 Application ကို စတင်ပါ

```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build/Desktop-Debug/setting_app
```

## 📱 UI သိရှိရန်

Application window မှာ အောက်ပါ အစိတ်အပိုင်းတွေ ရှိပါတယ်:

### 1. **Header** (အပေါ်ဆုံး)
- **Title**: "Robot WiFi Manager" 
- **Connection Indicator** (●):
  - 🔴 **Red တုန်ခါနေရင်** = Robot နဲ့ မချိတ်ထားသေးဘူး
  - 🟢 **Green ရပ်နေရင်** = Robot နဲ့ ချိတ်ပြီးပြီ

### 2. **Mode Selection**
- **Button**: "Switch to Bluetooth Mode" / "Switch to Ethernet Mode"
- **Label**: "Current Mode: Ethernet" သို့မဟုတ် "Bluetooth"

### 3. **Connection Controls**
- **Status**: Connection အခြေအနေပြတာ
- **[Connect]**: Robot နဲ့ ချိတ်/ဖြုတ် လုပ်တာ
- **[Refresh WiFi]**: WiFi status ကို refresh လုပ်တာ

### 4. **WiFi Information Display**
- **SSID**: လက်ရှိချိတ်ထားတဲ့ WiFi network name
- **Status**: Connection status (connected/disconnected)

### 5. **WiFi Change Form**
- **SSID Input**: အသစ် WiFi network name ရိုက်ရန်
- **Password Input**: WiFi password ရိုက်ရန်
- **[Change WiFi Network]**: ပြောင်းဖို့ button

### 6. **Status Log** (အောက်ဆုံး)
- Timestamp ပါတဲ့ messages တွေ
- Green = Success, Red = Error

## 📝 အသုံးပြုနည်း - အဆင့်အလိုက်

### Step 1: Robot Server ကို စတင်ပါ

**Robot Computer (Ubuntu 22.04) မှာ:**

```bash
# Terminal တစ်ခု ဖွင့်ပါ
cd /home/mr_robot/Desktop/Git/setting_app/setting_app

# Server ကို run ပါ
sudo python3 robot_server.py
```

**Output ကို စောင့်ပါ:**
```
INFO:__main__:HTTP server listening on port 8080
INFO:__main__:Bluetooth server listening on port 1
INFO:__main__:Robot WiFi Management Server started
```

### Step 2: Robot IP Address ကို စစ်ပါ

**Robot မှာ:**
```bash
ip addr show
# သို့မဟုတ်
hostname -I
```

**Example output:**
```
192.168.1.100  ← ဒီ IP ကို မှတ်ထားပါ
```

### Step 3: Application ကို ချိတ်ပါ

1. **Desktop Application** ကို စပါ
2. **Connection indicator** 🔴 Red တုန်ခါနေရင် ready ဖြစ်ပြီ
3. **"Connect" button** ကို နှိပ်ပါ
4. စောင့်ပါ... (1-2 စက္ကန့်)

**အောင်မြင်ရင်:**
- ● ← **Green** ဖြစ်သွားမယ်
- Status: **"Connected"**
- Log: `[hh:mm:ss] Connected to robot successfully`
- WiFi status auto-refresh လုပ်မယ်

**မအောင်မြင်ရင်:**
- Error message မြင်ရမယ်
- IP address စစ်ပါ (default: 192.168.1.100)
- Network connection စစ်ပါ

### Step 4: WiFi Status ကြည့်ပါ

Connected ဖြစ်ပြီဆိုရင် automatic ပြပေးမယ်:

```
Current WiFi Network
SSID: MyHomeWiFi
Status: connected
```

**Manual refresh လုပ်ချင်ရင်:**
- **"Refresh WiFi" button** ကို နှိပ်ပါ

### Step 5: WiFi Network ပြောင်းပါ

1. **"Enter new WiFi SSID"** field မှာ network name ရိုက်ပါ
   ```
   Example: Office-WiFi-5G
   ```

2. **"Enter WiFi password"** field မှာ password ရိုက်ပါ
   ```
   Example: MySecurePassword123
   ```
   
   💡 **Tip**: Open network (password မလို) ဆိုရင် ကွက်လပ်ထားလို့ရတယ်

3. **"Change WiFi Network" button** ကို နှိပ်ပါ

4. **Status log** မှာ progress ကြည့်ပါ:
   ```
   [14:30:10] Changing WiFi to: Office-WiFi-5G
   [14:30:15] WiFi changed successfully!
   [14:30:17] WiFi Status - SSID: Office-WiFi-5G, Status: connected
   ```

## ⚙️ Configuration (လိုအပ်ရင်)

### Robot IP Address ပြောင်းချင်ရင်

Default IP: `192.168.1.100`

**သင့် robot IP မတူရင်:**

1. **File ကို edit လုပ်ပါ:**
   ```bash
   nano networkmanager.cpp
   ```

2. **Line 14 ဝန်းကျင်မှာ ရှာပါ:**
   ```cpp
   m_robotIpAddress("192.168.1.100")
   ```

3. **သင့် robot IP နဲ့ ပြောင်းပါ:**
   ```cpp
   m_robotIpAddress("192.168.1.50")  // သင့် IP
   ```

4. **Rebuild လုပ်ပါ:**
   ```bash
   ./build_desktop.sh
   ```

## 🐛 အဖြစ်များတဲ့ ပြဿနာများ

### ပြဿနာ 1: "Connection refused"

**အကြောင်းရင်းများ:**
- Robot server မ run ထားဘူး
- IP address မှားနေတယ်
- Firewall block လုပ်နေတယ်

**ဖြေရှင်းနည်း:**
```bash
# Robot မှာ server run နေလား စစ်ပါ
ps aux | grep robot_server

# Port စစ်ပါ
sudo netstat -tlnp | grep 8080

# Desktop ကနေ test လုပ်ပါ
curl http://192.168.1.100:8080/api/wifi/status
```

### ပြဿနာ 2: WiFi မပြောင်းနိုင်ဘူး

**ဖြေရှင်းနည်း:**
```bash
# Robot မှာ NetworkManager စစ်ပါ
systemctl status NetworkManager

# Manual test
nmcli dev wifi connect "TestWiFi" password "test123"

# Server ကို sudo နဲ့ run ထားဖို့ အရေးကြီးတယ်
sudo python3 robot_server.py
```

### ပြဿနာ 3: Virtual Keyboard မပေါ်ဘူး

Desktop version မှာ virtual keyboard က အလုပ်လုပ်ပေမယ့် သိပ် မလိုအပ်ပါဘူး။ Desktop keyboard သုံးလို့ရပါတယ်။

## 🎯 အသုံးပြုမှု Example

### Scenario: Robot ရဲ့ WiFi ကို အိမ်ကနေ Office ကို ပြောင်းမယ်

```
1. Desktop app ဖွင့်ပါ
   ./build/Desktop-Debug/setting_app

2. Robot server run ထားပါ (Robot PC မှာ)
   sudo python3 robot_server.py

3. App မှာ "Connect" နှိပ်ပါ
   ● Green ဖြစ်ရင် ready

4. လက်ရှိ WiFi ကြည့်ပါ
   SSID: HomeWiFi
   Status: connected

5. Office WiFi အသစ် ထည့်ပါ
   SSID: OfficeWiFi-5G
   Password: Office@2024

6. "Change WiFi Network" နှိပ်ပါ

7. Log ကို ကြည့်ပါ
   ✅ WiFi changed successfully!
   
8. Refresh လုပ်ပါ
   SSID: OfficeWiFi-5G
   Status: connected

9. ပြီးပါပြီ! ✅
```

## 📊 Status Messages ဖတ်ပုံ

### Green Messages (အောင်မြင်မှု)
```
[14:30:45] Connected to robot successfully
[14:30:46] WiFi Status - SSID: MyWiFi, Status: connected
[14:31:10] WiFi changed successfully!
```

### Red Messages (အမှားတွေ)
```
[14:30:45] Error: Ethernet error: Connection refused
[14:31:00] Not connected to robot
[14:32:00] WiFi change failed: command failed
```

## 💡 အကြံပြုချက်များ

### 1. Network Configuration
- Robot နဲ့ Desktop ကို တူညီတဲ့ network မှာ ထားပါ
- Static IP သုံးရင် ပို stable ဖြစ်ပါတယ်

### 2. Security
- Production မှာ သုံးရင် authentication ထည့်ပါ
- Password တွေကို encrypt လုပ်ပါ

### 3. Testing
- ပထမဆုံး WiFi status refresh ကို test လုပ်ပါ
- ပြီးမှ WiFi change လုပ်ပါ
- ဘေးကင်ဘဲ WiFi network မှာ test လုပ်ပါ

## 🔧 Advanced Tips

### Desktop ကနေ Robot ကို Remote Access လုပ်ချင်ရင်

```bash
# SSH နဲ့ ချိတ်ပါ
ssh user@192.168.1.100

# Server ကို background မှာ run ပါ
nohup sudo python3 robot_server.py &

# Log ကြည့်ပါ
tail -f nohup.out
```

### Multiple Robots စီမံချင်ရင်

IP address တွေ မှတ်ထားပြီး code မှာ ပြောင်းပြီး rebuild လုပ်ပါ။

## 📚 နောက်ထပ် အချက်အလက်များ

- **Technical Details**: `README.md`
- **Architecture**: `ARCHITECTURE.md`
- **Full Documentation**: `DESKTOP_USAGE_MM.md` (အသေးစိတ်)

## ✅ Success!

Desktop version က အဆင်ပြေပြီဆိုရင်:
- UI test လုပ်ပြီးပြီ ✅
- Network communication test ပြီးပြီ ✅
- WiFi management စမ်းပြီးပြီ ✅

Android version အတွက် build ချင်ရင် `QT_CREATOR_SETUP.md` ကို ကြည့်ပါ။

**အောင်မြင်ပါစေ!** 🎉