#!/bin/bash

# Setup xrandr monitor
# xrandr --output OUTPUT --mode 1920x1080 -r 60

# Set wallpaper
WP_FILE="/home/${USER}/.local/dwm/wallpapers/wallpaper.jpg"
feh --bg-fill $WP_FILE

# Startup volume
# pactl set-sink-volume 0 20%

# Startup bar
/home/$USER/.local/dwm/sbar &

