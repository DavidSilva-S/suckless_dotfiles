#!/bin/env sh

# INIT
printf "$$" > ~/.cache/pidofbar
sec=0

# MODULES
update_cpu () { 
	cpu="$(grep -o "^[^ ]*" /proc/loadavg )" 
}

update_memory () { 
	memory=" $(free -h | sed -n "2s/\([^ ]* *\)\{2\}\([^ ]*\).*/\2/p")"
}

update_time () { 
	time=" $(date "+[%a %d %b] [%I:%M %P]")" 
}

update_weather () { 
	weather="$(curl -s "wttr.in?format=1"| sed -E "s/^(.).*\+/\1/")" 
}

update_bat () { 
	# you might need to change the path depending on your device
	read -r bat_status </sys/class/power_supply/BAT0/status
	read -r bat_capacity </sys/class/power_supply/BAT0/capacity
	bat="  $bat_status $bat_capacity%"
}

update_vol () { 
	# vol="墳 $([ "$(pamixer --get-mute)" = "false" ] && printf '🔊' || printf '🔇')$(pamixer --get-volume)%"
	vol="墳 $([ "$(pamixer --get-mute)" = "false" ])$(pamixer --get-volume)%"
}

update_backlight () { 
	# you might need to change the path depending on your device
	read -r actual_brightness </sys/class/backlight/intel_backlight/actual_brightness
	read -r max_brightness </sys/class/backlight/intel_backlight/max_brightness
	backlight="ﯧ $((actual_brightness*100/max_brightness))%"
}

# For calcurse users, refer https://github.com/pystardust/automeet
#update_event () { 
#	event="$(calcurse -n | sed 1d | \
#		sed -E "s_^ *\[(.*):(.*)\] ([^\t]*)\t?.*_[\1h \2m->\3]_")" 
#	[ "[]" = "$event" ] && event=""
#}


# modules that don't update on their own need to be run at the start for getting their initial value
update_vol
update_backlight

display () { 
	#printf "%s\n" " $event [$memory $cpu] [$bat] [$backlight] [$vol] [$time] "
	xsetroot -name " [$memory $cpu] [$bat] [$backlight] [$vol] [$time] "
}

# SIGNALLING
# trap	"<function>;display"		"RTMIN+n"
trap	"update_vol;display"		"RTMIN"
trap	"update_backlight;display" 	"RTMIN+1"
trap	"update_bat;display" 		"RTMIN+2"
# to update it from external commands
## kill -m "$(cat ~/.cache/pidofbar)"
# where m = 34 + n

while true
do
	sleep 1 & wait && { 
		# to update item ever n seconds with a offset of m
		## [ $((sec % n)) -eq m ] && udpate_item
		[ $((sec % 5 )) -eq 0 ] && update_time 	# update time every 5 seconds
		[ $((sec % 15)) -eq 0 ] && update_cpu 	# update cpu every 15 seconds
		[ $((sec % 15)) -eq 0 ] && update_memory
		[ $((sec % 60)) -eq 0 ] && update_bat
		
	        #[ $((sec % 5)) -eq 0 ] && update_vol 
		#[ $((sec % 300)) -eq 1 ] && update_event

		# how often the display updates ( 5 seconds )
		[ $((sec % 2 )) -eq 0 ] && display
		sec=$((sec + 1))
	}
done 


