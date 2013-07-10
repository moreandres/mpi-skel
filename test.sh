for size in 29 30 31 32 33 34;
do
echo $size
export N=$size
time src/queens
done
