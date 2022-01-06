#!/bin/bash

# Setup dual monitor
/home/$USER/.config/dwm/rightvert.sh

# Set wallpaper
WP_DIR="/home/m4t1/.local/share/wallpapers"
LEFT="4k-wall.jpg"
RIGHT="wall.png"
feh --bg-tile $WP_DIR/$LEFT --bg-fill $WP_DIR/$RIGHT

# Startup volume
pactl set-sink-volume 0 20%

# Startup bar
/usr/local/share/dwm/sbar &

# Mount MegaNZ drive
rclone mount Mega: /home/$USER/MegaNZ/ &

# Transparency - WARNING - Transparency couses a big lag on my pc!
# /usr/bin/picom -b

