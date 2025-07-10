#!/bin/bash

LOG_FILE="sys_monitor.log"
ARCHIVE_DIR="archives"
BACKUP_DIR="backup"
mkdir -p "$ARCHIVE_DIR" "$BACKUP_DIR"

print_header() {
    echo "======================================="
    echo "   SYSTEM MONITOR & MAINTENANCE TOOL   "
    echo "======================================="
}

log() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> "$LOG_FILE"
}

show_system_info() {
    echo "[*] System Information:"
    uname -a
    lsb_release -a 2>/dev/null
    uptime
    log "Checked system info"
}

show_disk_usage() {
    echo "[*] Disk Usage:"
    df -h
    log "Checked disk usage"
}

show_memory_usage() {
    echo "[*] Memory Usage:"
    free -h
    log "Checked memory usage"
}

show_top_processes() {
    echo "[*] Top 10 Processes by Memory:"
    ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head -n 11
    log "Checked top memory processes"
}

backup_home() {
    TIMESTAMP=$(date '+%Y%m%d%H%M%S')
    tar -czf "$BACKUP_DIR/home_backup_$TIMESTAMP.tar.gz" /home/"$USER" 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "[+] Backup successful: home_backup_$TIMESTAMP.tar.gz"
        log "Home backup created"
    else
        echo "[!] Backup failed"
        log "Home backup failed"
    fi
}

clean_temp_files() {
    echo "[*] Cleaning /tmp older than 7 days..."
    find /tmp -type f -mtime +7 -exec rm -f {} \;
    log "Cleaned temp files"
}

archive_logs() {
    TIMESTAMP=$(date '+%Y%m%d%H%M%S')
    tar -czf "$ARCHIVE_DIR/log_archive_$TIMESTAMP.tar.gz" "$LOG_FILE"
    echo "[+] Log archived as log_archive_$TIMESTAMP.tar.gz"
    log "Logs archived"
}

show_users() {
    echo "[*] Currently Logged In Users:"
    who
    log "Listed logged-in users"
}

kill_process() {
    read -p "Enter PID to kill: " pid
    if kill "$pid" 2>/dev/null; then
        echo "[+] Process $pid killed"
        log "Killed process $pid"
    else
        echo "[!] Failed to kill process $pid"
        log "Failed to kill process $pid"
    fi
}

menu() {
    echo
    echo "Choose an option:"
    echo "1. Show System Info"
    echo "2. Show Disk Usage"
    echo "3. Show Memory Usage"
    echo "4. Show Top Processes"
    echo "5. Backup Home Directory"
    echo "6. Clean Temp Files"
    echo "7. Archive Logs"
    echo "8. Show Logged-in Users"
    echo "9. Kill a Process"
    echo "10. Exit"
    echo
}

main_loop() {
    while true; do
        menu
        read -p "Enter your choice [1-10]: " choice
        case $choice in
            1) show_system_info ;;
            2) show_disk_usage ;;
            3) show_memory_usage ;;
            4) show_top_processes ;;
            5) backup_home ;;
            6) clean_temp_files ;;
            7) archive_logs ;;
            8) show_users ;;
            9) kill_process ;;
            10)
                echo "Exiting..."
                log "Exited script"
                break
                ;;
            *) echo "Invalid choice. Try again." ;;
        esac
        echo
    done
}

# ===========================
# Main Program Entry Point
# ===========================
clear
print_header
main_loop




To Run:

chmod +x system_monitor.sh
./system_monitor.sh
