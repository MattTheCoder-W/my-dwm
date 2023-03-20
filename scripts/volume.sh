#!/bin/bash

get_vol() {
	volume=$(awk -F"[][]" '/%/ { print $2 }' <(amixer sget Master) | head -n 1)
	vol_val=$(echo $volume | sed 's/%//g')
	echo $vol_val
}

action=$1
sink=1

if [[ "$action" == "up" ]]; then
	/usr/bin/pactl set-sink-volume $sink +5%
	if [[ $(get_vol) -gt 100 ]]; then
		/usr/bin/pactl set-sink-volume $sink 100%
	else
		/home/$USER/.local/dwm/refbar
	fi
elif [[ "$action" == "small-up" ]]; then
	/usr/bin/pactl set-sink-volume $sink +1%
	if [[ $(get_vol) -gt 100 ]]; then
		/usr/bin/pactl set-sink-volume $sink 100%
	else
		/home/$USER/.local/dwm/refbar
	fi
elif [[ "$action" == "down" ]]; then
	/usr/bin/pactl set-sink-volume $sink -5%
	/home/$USER/.local/dwm/refbar
elif [[ "$action" == "small-down" ]]; then
	/usr/bin/pactl set-sink-volume $sink -1%
	/home/$USER/.local/dwm/refbar
elif [[ "$action" == "mute" ]]; then
	/usr/bin/pactl set-sink-mute $sink toggle
	/home/$USER/.local/dwm/refbar
fi
