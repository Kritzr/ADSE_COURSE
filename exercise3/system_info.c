#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <string.h>

void print_os_info() {
    FILE *fp = fopen("/etc/os-release", "r");
    char line[256];
    printf("OS info:\n");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "PRETTY_NAME", 11) == 0) {
                char *os_name = strchr(line, '=');
                if (os_name) {
                    printf("  OS: %s", os_name + 1);
                }
                break;
            }
        }
        fclose(fp);
    }
}

void print_cpu_info() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    char line[256];
    printf("\nCPU Information:\n");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "model name", 10) == 0) {
                printf("  Model: %s", strchr(line, ':') + 2);
                break;
            }
        }
        fclose(fp);
    }
}

void print_mem_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    char line[256];
    printf("\tmemory info\n");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "MemTotal", 8) == 0) {
                printf("  Total RAM: %s", strchr(line, ':') + 2);
                break;
            }
        }
        fclose(fp);
    }
}

void print_disk_info() {
    printf("\tDisk info:\n");
    system("df -h --total | grep total");
}

void print_sysinfo() {
    struct sysinfo info;
    sysinfo(&info);
    printf("\tsystem uptime: %ld seconds\n", info.uptime);
    printf("total RAM: %ld MB\n", info.totalram / (1024 * 1024));
    printf("free RAM: %ld MB\n", info.freeram / (1024 * 1024));
    printf("no of processes: %d\n", info.procs);
}

void print_uname_info() {
    struct utsname buffer;
    if (uname(&buffer) != -1) {
        printf("\nSystem Info (uname):\n");
        printf("  sysname: %s\n", buffer.sysname);
        printf("  nodename: %s\n", buffer.nodename);
        printf("  release: %s\n", buffer.release);
        printf("  version: %s\n", buffer.version);
        printf("  machine: %s\n", buffer.machine);
    }
}

void print_hostname() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    printf("\thostname: %s\n", hostname);
}

void print_page_size() {
    long page_size = sysconf(_SC_PAGESIZE);
    printf("\tpage size: %ld bytes\n", page_size);
}

int main() {
    printf("ystem configuration details \n");
    print_os_info();
    print_uname_info();
    print_hostname();
    print_cpu_info();
    print_mem_info();
    print_sysinfo();
    print_disk_info();
    print_page_size();
    printf("\n========================================\n");
    return 0;
}

