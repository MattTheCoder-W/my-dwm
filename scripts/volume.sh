#!/bin/bash

get_vol() {
	volume=$(awk -F"[][]" '/%/ { print $2 }' <(amixer sget Master) | head -n 1)
	vol_val=$(echo $volume | sed 's/%//g')
	echo $vol_val
}

action=$1

if [[ "$action" == "up" ]]; then
	/usr/bin/pactl set-sink-volume 0 +5%
	if [[ $(get_vol) -gt 100 ]]; then
		/usr/bin/pactl set-sink-volume 0 100%
	fi
elif [[ "$action" == "down" ]]; then
	/usr/bin/pactl set-sink-volume 0 -5%
elif [[ "$action" == "mute" ]]; then
	/usr/bin/pactl set-sink-mute 0 toggle
fi
