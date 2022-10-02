old=60
while [[ 1 -eq 1 ]]; do
	if [[ ! "$old" -eq "$(date +%M)" ]]; then
		old=$(date +%M);
		/home/$USER/.config/dwm/cyber-wallpaper/make-wallpaper.py;
	else
		sleep 1;
	fi
done
