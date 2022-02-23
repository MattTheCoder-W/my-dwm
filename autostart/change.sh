#!/bin/bash

state=$(cat /home/$USER/.config/dwm/state.txt)
if [[ "$state" == "0" ]]; then
	feh --bg-tile /home/$USER/.config/dwm/wallpapers/anime-wallpaper.jpg --bg-fill /home/$USER/.config/dwm/wallpapers/right.jpg
	state="1"
	echo $state > /home/$USER/.config/dwm/state.txt
else
	feh --bg-tile /home/$USER/.config/dwm/wallpapers/left.jpg --bg-fill /home/$USER/.config/dwm/wallpapers/right.jpg
	state="0"
	echo $state > /home/$USER/.config/dwm/state.txt
fi

cat /home/$USER/.config/dwm/state.txt
