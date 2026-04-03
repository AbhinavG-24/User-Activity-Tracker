# 🔍 User Activity Tracker

> **A Unix-based system monitoring tool written in C and Bash Shell Scripting that automates the tracking of user login sessions, detects unauthorized access in real-time, and generates dated activity reports — using Unix system-level APIs and shell automation.**

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)
2. [Key Features](#key-features)
3. [System Requirements](#system-requirements)
4. [Tools & Technologies](#tools--technologies)
5. [Project Structure](#project-structure)
6. [How It Works](#how-it-works)
7. [How to Run](#how-to-run)
8. [Sample Output](#sample-output)
9. [Algorithm & Complexity](#algorithm--complexity)
10. [Future Roadmap](#future-roadmap)
11. [References](#references)

---

## 🏛️ Project Overview

In multi-user Unix systems, multiple users can be logged in simultaneously for various tasks — programming, data processing, or system maintenance. Manual monitoring of user sessions is inefficient, error-prone, and insecure at scale.

The **User Activity Tracker** is a console-based Unix tool that automates this process entirely. Written in **C** (for system-level access) and **Bash** (for automation), it reads live login records via the `utmpx` Unix API, cross-checks users against an authorized list, flags unauthorized logins with real-time alerts, and archives daily reports — all without any manual intervention.

---

## ✨ Key Features

| Feature | Description |
|---|---|
| 👥 Live Session Monitoring | Reads active user sessions in real-time using Unix `getutxent()` and `utmpx.h` |
| 🔐 Unauthorized Access Detection | Cross-checks each logged-in user against `allowed_users.txt`; flags unknown users as `⚠️ ALERT` |
| 📄 Automated Report Generation | Generates formatted `.txt` reports with username, terminal, login time, and access status |
| 📁 Daily Report Archiving | Shell script automatically moves each report to a dated folder (`~/user_reports/YYYY-MM-DD`) |
| 🔔 Real-Time Terminal Alerts | Prints red-colored warnings and triggers desktop notifications for unauthorized logins |
| 🔄 Shell Automation | Bash wrapper script compiles the C program, runs it, and archives results in one command |

---

## 🖥️ System Requirements

### Software Requirements

| Component | Requirement |
|---|---|
| **Language** | C (with GCC compiler) + Bash Shell Scripting |
| **OS** | Linux / Unix |
| **Compiler** | GCC (GNU Compiler Collection) |
| **Shell** | Bash (Bourne Again Shell) |
| **Libraries** | `<stdio.h>`, `<stdlib.h>`, `<utmpx.h>`, `<time.h>`, `<string.h>` |

### Hardware Requirements

| Component | Minimum |
|---|---|
| Processor | Intel/AMD, 1 GHz or higher |
| RAM | 512 MB |
| Disk Space | 10 MB (for logs and reports) |

---

## 🛠️ Tools & Technologies

| Tool | Purpose |
|---|---|
| **C Language** | System-level programming; reads Unix login records via `utmpx` API |
| **Bash Scripting** | Automates compilation, execution, and report archiving |
| **GCC** | Compiles the C source file |
| **`getutxent()` / `utmpx.h`** | Unix API for reading active user login sessions |
| **`cron`** (optional) | Schedules the tracker to run automatically at set intervals |
| **`notify-send`** | Desktop notifications for unauthorized login alerts |

---

## 📁 Project Structure

```
user-activity-tracker/
├── user_tracker.c          # Core C program — reads sessions, checks auth, writes report
├── user_tracker.sh         # Bash wrapper — compiles, runs, and archives the report
├── allowed_users.txt       # Whitelist of authorized usernames (one per line)
├── reports/
│   └── user_activity_report.txt   # Generated on each run
├── ~/user_reports/
│   └── user_report_YYYY-MM-DD.txt # Archived dated reports
└── README.md
```

---

## ⚙️ How It Works

```
┌─────────────────────────────────────────────────────┐
│              user_tracker.sh (Shell)                │
│  1. Compiles user_tracker.c using gcc               │
│  2. Runs ./users_tracker                            │
│  3. Moves report to ~/user_reports/YYYY-MM-DD/      │
│  4. Displays report on terminal                     │
└───────────────────┬─────────────────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────────────┐
│              user_tracker.c (C Program)             │
│  1. Load allowed_users.txt into memory              │
│  2. Open utmpx database (setutxent)                 │
│  3. For each USER_PROCESS entry:                    │
│     ├── Format login timestamp                      │
│     ├── Check if username is in allowed list        │
│     ├── If YES → write "Normal" to report           │
│     └── If NO  → write "ALERT!" + trigger warning  │
│  4. Save full report to reports/user_activity_report│
└─────────────────────────────────────────────────────┘
```

---

## 🚀 How to Run

### Prerequisites
- GCC installed: `sudo apt install gcc`
- Bash shell (default on all Linux/Unix systems)

### Step 1 — Add Authorized Users

Edit `allowed_users.txt` and list one authorized username per line:

```
root
student1
student2
abhinav
```

### Step 2 — Make the Shell Script Executable

```bash
chmod +x user_tracker.sh
```

### Step 3 — Run the Tracker

```bash
./user_tracker.sh
```

> 💡 The `reports/` directory and report files are created automatically on the first run.

### Optional — Schedule with Cron (Auto-run daily)

```bash
crontab -e
# Add this line to run every day at midnight:
0 0 * * * /path/to/user_tracker.sh
```

---

## 📊 Sample Output

```
========== User Activity Report for 2025-03-15 ==========
==============================================================
 USER ACTIVITY TRACKER REPORT
==============================================================
Username        Terminal        Login Time            Status
-------------------------------------------------------------
root            tty1            2025-03-15 08:30:21   Normal
abhinav         pts/0           2025-03-15 09:15:44   Normal
unknown_user    pts/1           2025-03-15 09:45:10   ALERT!
==============================================================

⚠️  ALERT: Unauthorized user 'unknown_user' logged in at 2025-03-15 09:45:10
```

---

## 📐 Algorithm & Complexity

| Task | Algorithm | Time Complexity |
|---|---|---|
| Loading Allowed Users | File Read (linear scan) | O(n) |
| Checking Authorization | String comparison per user | O(n × m) |
| Report Generation | Sequential File Write | O(n) |

> where `n` = number of logged-in users, `m` = number of allowed users

---

## 🔭 Future Roadmap

- [ ] **Email Alerts** — Notify admin via `mail` command on unauthorized login
- [ ] **Web Dashboard** — Visual analytics of user activity over time
- [ ] **Database Integration** — Persistent log storage using MySQL or SQLite
- [ ] **CSV / HTML Reports** — Export reports in structured formats for analysis
- [ ] **Multi-system Support** — Extend monitoring across networked Unix machines
- [ ] **Cron Integration Wizard** — Interactive script to set up automated scheduling

---

## 📚 References

1. Sobell, M. G. (2017). *A Practical Guide to Linux Commands, Editors, and Shell Programming* (4th ed.). Addison-Wesley.
2. Unix Manual Pages: `man who`, `man last`, `man cron`, `man utmpx`
3. [TutorialsPoint — Unix Shell Scripting](https://www.tutorialspoint.com/unix/shell_scripting.htm)
4. [GeeksforGeeks — Unix Programming Concepts](https://www.geeksforgeeks.org)

---

*Built with ❤️ · Unix Programming 
