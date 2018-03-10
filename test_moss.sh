old_dir="old_game"
if [ ! -d "$old_dir" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  mkdir $old_dir
  cd $old_dir
  git clone https://github.com/shubhMaheshwari/Opengl-3d.git
  cd ..
fi


./moss src/* ./old_game/Opengl-3d/src/*