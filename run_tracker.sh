#!/bin/bash
# User Activity Tracker -Shell Wrapper
TODAY=$(date +%Y-%m-%d)
REPORT_DIR="$HOME/user_reports"
mkdir -p "$REPORT_DIR"

#Compile the C program
gcc users_tracker.c -o users_tracker
#Run the program
./users_tracker

#Move report to dated folder
mv user_report.txt "$REPORT_DIR/user_report_$TODAY.txt"
echo "Report saved to $REPORT_DIR/user_report_$TODAY.txt"
