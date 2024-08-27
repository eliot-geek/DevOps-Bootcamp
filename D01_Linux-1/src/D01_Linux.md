## Part 1. Installation of the OS

- **Install Ubuntu 20.04 Server LTS on VirtualBox**
- **Verification of Ubuntu Version**

    ![Ubuntu Version Verification](./images/part1.png "Ubuntu 20.04 Server LTS Verification")

---

## Part 2. Creating a User

- **Create a New User and Add to `adm` Group**
    ```sh
    sudo useradd adm new_user
    sudo useradd -G adm -s /bin/bash -p 12345 new_user
    ```
    ![Create New User](./images/part2_create_user.png "Command to Create New User and Add to adm Group")

- **Verify the New User in `/etc/passwd`**
    ```sh
    cat /etc/passwd
    ```
    ![Verify New User](./images/part2_verify_user.png "Verification of New User in /etc/passwd")

---

## Part 3. Setting up the OS Network

### 1. **Set the Machine Name**

- **Command to Set Hostname:**
    ```sh
    sudo hostnamectl set-hostname user-1
    ```

    ![Set Hostname](./images/part3_set_hostname.png "Command to Set Machine Name as user-1")

### 2. **Set the Time Zone**

- **Command to Set Time Zone:**
    ```sh
    sudo timedatectl set-timezone Europe/Moscow
    ```

    ![Set Time Zone](./images/part3_set_timezone.png "Command to Set Time Zone")

### 3. **Output the Names of the Network Interfaces**

- **Command to List Network Interfaces:**
    ```sh
    ip a / ip link show / ip -br a show
    ```

    ![List Network Interfaces](./images/part3_list_interfaces.png "Output of Network Interfaces")

- **Explanation for the Presence of the `lo` Interface**

    The `lo` interface is the loopback interface. It is a special, virtual network interface that a computer uses to communicate with itself. The IP address for `lo` is typically `127.0.0.1`. It is used primarily for testing and debugging.

### 4. **Get the IP Address from the DHCP Server**

- **Command to Get IP Address:**
    ```sh
    ip --color r / sudo dhclient -v enp0s3
    ```

    ![Get IP Address](./images/part3_get_ip.png "Command to Get IP Address from DHCP Server")

- **DHCP Explanation:**
    DHCP (Dynamic Host Configuration Protocol) is a network management protocol used to automate the process of configuring devices on IP networks. It dynamically assigns IP addresses and other network configuration parameters to devices, allowing them to communicate on the network without needing manual configuration.

### 5. **Define and Display External and Internal IP Addresses of the Gateway**

- **Command to Display Gateway IPs:**
    ```sh
    ip --color route | grep default
    ```

    ![Display Gateway IPs](./images/part3_gateway_ips1.png "Command to Display External and Internal IP Addresses of the Gateway")

    - External IP address of the gateway can be found by:
    ```sh
    curl icanhazip.com
    ```

    ![Display Gateway IPs](./images/part3_gateway_ips2.png "Command to Display External and Internal IP Addresses of the Gateway")

### 6. **Set Static Network Settings**

- **Edit Network Configuration File:**
    ```sh
    sudo nano /etc/netplan/00-installer-config.yaml
    ```

    ![Edit Network Configuration](./images/part3_static_network_settings1.png "Setting Static Network Configuration")

    ![Edit Network Configuration](./images/part3_static_network_settings2.png "Setting Static Network Configuration")

    ```sh
    sudo netplan apply
    ```
    - Apply network configuration changes.
    - Ensure the changes take effect immediately.
    - Execute with the required administrative privileges.  <p>

    ![Edit Network Configuration](./images/part3_static_network_settings3.png "Setting Static Network Configuration")

- **Reboot the Virtual Machine:**
    ```sh
    sudo reboot
    ```
- **Ping Commands:**
    ```sh
    ping 1.1.1.1
    ping ya.ru
    ```

    ![Ping 1.1.1.1 Ping ya.ru](./images/part3_ping_1.1.1.1part3_ping_yaru.png "Ping to 1.1.1.1 Ping to ya.ru")

---
## Part 4. OS Update

### 1. **Update System Packages**

- **Update Command:**
    ```sh
    sudo apt update && sudo apt-get upgrade -y
    ```

    ![Update System Packages](./images/part4_update_packages.png "Updating System Packages")

---

## Part 5. Using the sudo Command

### 1. **Allow User to Execute `sudo` Command**

- **Add User to `sudo` Group:**
    ```sh
    sudo usermod -aG sudo new_user
    ```
- **Change Hostname:**
    ```sh
    sudo hostnamectl set-hostname new-hostname
    ```

    ![Add User to sudo Group](./images/part5_add_user_sudo.png "Command to Add User to sudo Group")

- **Purpose of `sudo`:**
    The `sudo` command allows a permitted user to execute a command as the superuser or another user, as specified by the security policy. It is a way to temporarily elevate privileges to perform tasks that require root or administrative permissions. This is useful for managing system settings, installing software, and performing administrative tasks without logging in as the root user, thereby maintaining system security.

---

## Part 6. Installing and Configuring the Time Service

- **Enable and Start the Time Synchronization Service**
    ```sh
    sudo systemctl enable systemd-timesyncd
    sudo systemctl start systemd-timesyncd
    
- **Check Current Time:**
    ```sh
    timedatectl
    ```

- **Check NTP Synchronization:**
    ```sh
    timedatectl show
    ```

    - Expected Output: `NTPSynchronized=yes`

    ![Verify NTP Synchronization](./images/part6_ntp_sync.png "Verifying NTP Synchronization")

---

## Part 7. Installing and Using Text Editors

### 1. Install Text Editors

- **Install VIM, Nano, and Joe**
    ```sh
    sudo apt install vim nano joe
    ```
     ![Install VIM, Nano, and Joe](./images/part7_vim_nano_joe_install.png "Install VIM, Nano, and Joe")

     ![Install VIM, Nano, and Joe](./images/part7_vim_nano_joe_install1.png "Install VIM, Nano, and Joe")

### 2. Create a File with Each Editor

#### VIM
    vim test_vim.txt

- Steps to Exit and Save in VIM:
    - Press i to enter insert mode and write your nickname.
    - Press Esc to exit insert mode.
    - Type :wq and press Enter to save and quit.

    ![VIM Save and Exit](./images/part7_vim_save.png "VIM - Saving and Exiting with Nickname")

#### Nano
    nano test_nano.txt

- Steps to Exit and Save in Nano:
    - Write your nickname directly.
    - Press Ctrl + O to save the file, press Enter to confirm.
    - Press Ctrl + X to exit.

    ![Nano Save and Exit](./images/part7_nano_save.png "Nano - Saving and Exiting with Nickname")

#### Joe
    joe test_joe.txt

- Steps to Exit and Save in Joe:
    - Write your nickname directly.
    - Press Ctrl + K, then X to save and exit.

    ![Joe Save and Exit](./images/part7_joe_save.png "Joe - Saving and Exiting with Nickname")

### 3. Edit the File and Exit Without Saving

#### VIM

- Steps to Exit Without Saving in VIM:
    - Press i to enter insert mode and make changes.
    - Press Esc to exit insert mode.
    - Type :q! and press Enter to quit without saving.

    ![VIM Quit Without Saving](./images/part7_vim_quit.png "VIM - Quit Without Saving")

#### Nano

- Steps to Exit Without Saving in Nano:
    - Make changes directly.
    - Press Ctrl + X to exit, then press N to discard changes.

    ![Nano Quit Without Saving](./images/part7_nano_quit.png "Nano - Quit Without Saving")

#### Joe

- Steps to Exit Without Saving in Joe:
    - Make changes directly.
    - Press Ctrl + C to exit, then press Y to lose changes.

    ![Joe Quit Without Saving](./images/part7_joe_quit.png "Joe - Quit Without Saving")

### 4. Search and Replace in Each Editor

For each editor:

- Edit the File to replace a word.
- Search for the word in the file.
- Replace it with another word.

##### VIM

- Steps to Search and Replace in VIM:
    - Press Esc and type :/WordToSearch.
    - To replace, type :%s/WordToReplace/NewWord/g and press Enter.

    ![VIM Search and Replace](./images/part7_vim_replace.png "VIM - Search and Replace")
    ![VIM Search and Replace](./images/part7_vim_replace1.png "VIM - Search and Replace")

##### Nano

- Steps to Search and Replace in Nano:
    - Press Ctrl + W and type the word to search, press Enter.
    - Press Ctrl + \ and type the word to replace, press Enter.

    ![Nano Search and Replace](./images/part7_nano_replace.png "Nano - Search and Replace")
    ![Nano Search and Replace](./images/part7_nano_replace1.png "Nano - Search and Replace")
    ![Nano Search and Replace](./images/part7_nano_replace2.png "Nano - Search and Replace")

##### Joe

- Steps to Search and Replace in Joe:
    - Press Ctrl + K, then F to search.
    - Press Ctrl + K, then R to replace.

    ![Joe Search and Replace](./images/part7_joe_replace.png "Joe - Search and Replace")
    ![Joe Search and Replace](./images/part7_joe_replace.png "Joe - Search and Replace")
    ![Joe Search and Replace](./images/part7_joe_replace.png "Joe - Search and Replace")
    ![Joe Search and Replace](./images/part7_joe_replace.png "Joe - Search and Replace")

---

## Part 8. Installing and basic setup of the SSHD service

### 1. Install the SSHD Service

    sudo apt install openssh-server
    sudo apt install ssh

Installs the OpenSSH server package, which includes the SSH daemon (sshd).

![SSHD Installation](./images/part8_install_sshd.png "Installation of SSHD Service")
![SSHD Installation](./images/part8_install_sshd1.png "Installation of SSHD Service")

### 2. Enable SSHD Service to Start on Boot

To ensure the SSHD service starts automatically when the system boots:

    sudo systemctl enable ssh

Configures the SSHD service to start automatically on system boot.

![Enable SSHD Autostart](./images/part8_enable_autostart.png "Enable SSHD Autostart")

### 3. Change the SSHD Port to 2022

Enter the SSHD configuration file to change the port:

    sudo vim /etc/ssh/sshd_config

After making this change, restart the SSHD service to apply the changes:

    sudo systemctl restart ssh

![Change SSHD Port](./images/part8_change_port.png "Changing SSHD Port to 2022")
![Change SSHD Port](./images/part8_change_port2.png "Changing SSHD Port to 2022")

### 4. Show the Presence of the SSHD Process Using ps

To verify that the SSHD process is running:

    ps aux | grep sshd

- ps: Displays currently running processes.
- aux:
  - a: Shows processes for all users.
  - u: Displays the user/owner of the process. (includes user ID and memory usage).
  - x: Shows processes not attached to a terminal.
- | grep sshd: Filters the output to show only lines containing sshd.

![Verify SSHD Process](./images/part8_verify_process.png "Verifying SSHD Process with ps")

### 5. Reboot the System

Reboot the system to ensure all configurations take effect:

    sudo reboot

After the reboot, SSHD should start automatically on port 2022.

![Reboot the System](./images/part8_reboot_system.png "Reboot the System")

### 6. Verify SSHD Listening on Port 2022 Using netstat -tan

To check the SSHD service running on port 2022, use:

    sudo netstat -tan

- -t: Shows TCP connections.
- -a: Displays all active connections and the listening ports.
- -n: Displays addresses and port numbers in numerical form.

![Netstat Output](./images/part8_netstat_output1.png "Netstat Output Showing SSHD on Port 2022")

### Explanation of netstat -tan 

- Protocol (tcp): The protocol used (TCP).
- Recv-Q/Send-Q: Byte queues for receiving and sending data.
- Local Address (0.0.0.0:22): The local IP address and port number.
- Foreign Address (0.0.0.0:*): The remote IP address and port number (or * for any).
- State (LISTEN): Indicates the port is listening for incoming connections.

- tcp: The protocol used (Transmission Control Protocol).
- 0: The number of bytes in the receive queue.
- 0: The number of bytes in the send queue.
- 0.0.0.0:22: Listening on port 2022 on all available IP addresses (0.0.0.0 indicates any IP address).
- 0.0.0.0:: The destination address (* indicates any IP address).
- LISTEN: Indicates that the port is open and SSHD is waiting for incoming connections.

---

## Part 9: Installing and Using the top and htop Utilities

### 1. Install the top and htop Utilities

    sudo apt install htop

![Installing htop](./images/part9_install_htop.png "Installing the htop Utility")

### 2. Run the top Command and Extract Metrics

    top

- Uptime: 32 min.
- Number of Authorized Users: 1 user.
- Total System Load: 0.00, 0.00, 0.00 - the average system load over 1, 5, and 15 minutes.
- Total Number of Processes: 104.
- CPU Load: 0.0 us, 0.0 sy, 0.0 ni, 100.0 id, 0.0 wa, 0.0 hi. 0.0 si, 0.0 st
- Memory Load: 3920.0 total, 3375.0 free, 155.4 used, 389.6 buff/cache
- PID of the Process with the Highest Memory Usage: 1 - %MEM 0.3
- PID of the Process Taking the Most CPU Time: 1499 - %CPU 0.3

![Top Command Output](./images/part9_top_output.png "Output of the top Command")

### 3. Run the htop Command

    htop

1. Sorted by PID, PERCENT_CPU, PERCENT_MEM, TIME:
- Press F6 and select PID, %CPU, %MEM, or TIME
- PID
![htop Sorted by PID](./images/part9_htop_pid.png "htop Sorted by PID")
![htop Sorted by PID](./images/part9_htop_pid1.png "htop Sorted by PID")
- PERCENT_CPU
![htop Sorted by PERCENT_CPU](./images/part9_htop_cpu.png "htop Sorted by PERCENT_CPU")
- PERCENT_MEM
![htop Sorted by PERCENT_MEM](./images/part9_htop_mem.png "htop Sorted by PERCENT_MEM")
- TIME
![htop Sorted by TIME](./images/part9_htop_time.png "htop Sorted by TIME")

2. Filtered for SSHD Process:
- Press fn + F4 and type sshd to filter and display only the sshd processes.
![htop Filtered for SSHD](./images/part9_htop_sshd.png "htop Filtered for SSHD Process")

3. Search for the Syslog Process:
- Press fn + F3 and type syslog to search and highlight the syslog process.
- ![htop Syslog Search](./images/part9_htop_syslog.png "htop Search for Syslog Process")

4. Add Hostname, Clock, and Uptime Output:
- Press F2 to open the setup menu, navigate to the "Meters" section, and add Hostname, Clock, and Uptime to the display.

- ![htop with Hostname, Clock, Uptime](./images/part9_htop_hostname_clock_uptime.png "htop with Hostname, Clock, and Uptime Displayed")
- ![htop with Hostname, Clock, Uptime](./images/part9_htop_hostname_clock_uptime1.png "htop with Hostname, Clock, and Uptime Displayed")

---

## Part 10. Using the fdisk utility

### Step 1: Run the fdisk -l Command

    sudo fdisk -l

![fdisk output](./images/part10_fdisk_output.png "fdisk -l Output")

### Step 2: Identify the Information

    - Hard Disk Name: /dev/sda
    - Disk Capacity: 50 GiB  
    - Number of Sectors: 104 857 600  
    - Swap Size: 3.9 GB

![fdisk output](./images/part10_fdisk_output1.png "fdisk -l Output")

![fdisk output](./images/part10_fdisk_output2.png "fdisk -l Output")

---

## Part 11: Using the df Utility

### Output of the df Command for Root Partition (/):
    sudo df
    sudo df /
- Partition Size: 24 590 672
- Space Used: 7 218 720
- Space Free: 16 097 484
- Percentage Used: 31%

Measurement Unit: Kilobytes (KB)

![df output](./images/part11_df_output.png "df Output")

### Output of the df -Th Command for Root Partition (/):
    sudo df -Th
    sudo df -Th /

- Partition Size: 24G
- Space Used: 6.9G
- Space Free: 16G
- Percentage Used: 31%
- File System Type: ext4

![df -Th output](./images/part11_df_th_output.png "df -Th Output")

---

## Part 12: Using the du Utility

### Size of Directories in Human-Readable Format:
     sudo du -sh /home
     sudo du -sh /var
     sudo du -sh /var/log
     
- The -s option ensures that you get a summary (total size) of the directory.
- The -h option makes the output human-readable, showing sizes in KB, MB, GB, etc.

    ```
    /home: 92K
    /var: 829M
    /var/log: 29M
    ```

![du -sh output](./images/part12_du_sh_output.png "du -sh Output")

### Size of Each Element in /var/log:
    du -h /var/log/*
     
   - This command will display the size of each file and subdirectory inside /var/log.

![du -h /var/log/* output](./images/part12_du_var_log_output.png "du -h /var/log/* Output")
![du -h /var/log/* output](./images/part12_du_var_log_output1.png "du -h /var/log/* Output")

---

## Part 13: Installing and Using the `ncdu` Utility

### Step 1: Install the ncdu Utility

Install `ncdu`
```
sudo apt install ncdu
```
![install ncdu /home](./images/part13_install_ncdu_home.png "ncdu /home installation")

### Step 2: Use ncdu to Check Folder Sizes

Run `ncdu` for `/home`, `/var`, and `/var/log`:
```
sudo ncdu /home
sudo ncdu /var
sudo ncdu /var/log
```     

1. **/home directory size**:
   ![ncdu /home](./images/part13_ncdu_home.png "ncdu /home Output")
   ![ncdu /home](./images/part13_ncdu_home1.png "ncdu /home Output")

2. **/var directory size**:
   ![ncdu /var](./images/part13_ncdu_var.png "ncdu /var Output")

3. **/var/log directory size**:
   ![ncdu /var/log](./images/part13_ncdu_var_log.png "ncdu /var/log Output")

---

## Part 14: Working with System Logs
```
vim /etc/log/dmesg
```
![Auth Log Entry](./images/part14_auth_log_entry_dmesg.png "Auth Log Entry")
``` 
vim /etc/log/syslog 
```
![Auth Log Entry](./images/part14_auth_log_entry_syslog.png "Auth Log Entry")
```
vim /etc/log/auth.log
```
![Auth Log Entry](./images/part14_auth_log_entry_auth.png "Auth Log Entry")

### Last Successful Login Details:
```
cat /var/log/auth.log | grep systemd-logind
```
- Time: Aug  9 17:40:22
- Username: atruskat
- Login Method: Login

![Auth Log Entry](./images/part14_auth_log_entry.png "Auth Log Entry")
![Auth Log Entry](./images/part14_auth_log_entry1.png "Auth Log Entry")

### Restarting SSHd Service:
```
sudo systemctl restart sshd
grep ssh /var/log/auth.log
```
![Service Restart Message](./images/part14_service_restart1.png "Service Restart Message")

---

## Part 15: Using the CRON Job Scheduler

### Set Up CRON Job:
    crontab -e
![CRON crontab](./images/part15_cron_crontab.png "CRON crontab Log")

- CRON Job: Run uptime every 2 minutes.
- Add a New CRON Job:
```
*/2 * * * * uptime
```
     - */2: Every 2 minutes.
     - * * * * *: Every hour, day, month, and day of the week.
     - uptime: The command to run.

![CRON crontab](./images/part15_cron_crontab1.png "CRON crontab Log")


### List of Current CRON Jobs:
- Check that the CRON job has been added:
```
crontab -l
```
![Current CRON Jobs](./images/part15_cron_jobs.png "Current CRON Jobs")

### Uptime command:
- Check system logs to find lines about CRON job execution
```
grep -i CRON /var/log/syslog
```
![CRON Execution Log](./images/part15_cron_execution.png "CRON Execution Log")

### Remove All CRON Jobs
```
crontab -r
```
![Empty CRON Jobs List](./images/part15_empty_cron_jobs.png "Empty CRON Jobs List")


- After Removing All Jobs:
```
crontab -l
```
![Empty CRON Jobs List](./images/part15_empty_cron_jobs.png "Empty CRON Jobs List")

---