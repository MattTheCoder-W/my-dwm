#!/bin/bash

options="cancel\nshutdown\nreboot\nsleep"
answ=$(echo -e $options | dmenu)
if [[ "$answ" == "shutdown" ]]; then
	shutdown now
elif [[ "$answ" == "reboot" ]]; then
	reboot
elif [[ "$answ" == "sleep" ]]; then
	systemctl suspend
fi
