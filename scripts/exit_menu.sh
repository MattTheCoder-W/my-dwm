#!/bin/bash

shutdown_text="shutdown"
reboot_text="reboot"
sleep_text="sleep"
options="cancel\n$shutdown_text\n$reboot_text\n$sleep_text"
answ=$(echo -e $options | dmenu)
if [[ "$answ" == $shutdown_text ]]; then
	shutdown now
elif [[ "$answ" == $reboot_text ]]; then
	reboot
elif [[ "$answ" == $sleep_text ]]; then
	systemctl suspend
fi
