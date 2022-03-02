#!/bin/bash

# save current spread date and time
int_save() {
	echo $(date) > /home/$USER/.config/dwm/last-spread.dat
}

# check_missing "script1 script2 ..." "local_folder"
check_missing() {
	scripts=($1)
	folder=$2
	if [[ ! -d "$folder" ]]; then
		echo ">> scripts directory not found! pull repo again!"
		exit 1
	fi
	missing=0
	for script in ${scripts[@]}; do
		if [[ ! $(echo $(ls "$folder") | grep -w $script) ]]; then
			echo ">> script $script not found! pull repo again!"
			missing=1
		fi
	done
	if [[ $missing -eq 1 ]]; then
		echo ">> There are missing files in -> $folder"
		exit 1
	else
		echo ">> No missing files in -> $folder"
	fi
}

doas echo ">> START"

custom_scripts="sbar volume.sh refbar reconf exit_menu.sh"
autostart="dwm-autostart.sh int-check rightvert.sh change.sh disable-screen.sh"

check_missing "$custom_scripts" "scripts"
check_missing "$autostart" "autostart"

dir="/usr/local/share/dwm /home/$USER/.config/dwm"
for place in $dir; do
	if [[ ! -d "$place" ]]; then
		echo ">> Creating $place"
		sudo mkdir -p $place
	fi
done

echo ">> Copying..."

echo -e "\t>> Copying scripts"
for script in $custom_scripts; do
	echo -e "\t\t>> Copying $script"
	sudo cp scripts/$script /usr/local/share/dwm/$script
done

echo -e "\t>> Copying autostart files"
for script in $autostart; do
	echo -e "\t\t>> Copying $script"
	cp autostart/$script /home/$USER/.config/dwm/$script
done

int_save

echo ">> DONE!"
