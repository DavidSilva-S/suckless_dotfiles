#! /bin/env sh

if [[ $LANG = "pt_BR.UTF-8" ]]; then
	echo "iniando script..."
else
	echo "starting script..."
fi



echo "creating folders..."
mkdir -p Imagens/ && mkdir -p .conf/suckless

echo "copying dot files..."
cp -f -r dwm /root/$HOME/.config/suckless




