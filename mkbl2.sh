file=$1
out="bl2.img"

if [ $# != 1 ]; then
	echo "(usage) mkbl2.sh [bl2.bin]"
	exit 1
fi

if [ -f ${out} ];then
	echo ${out} already exists.
	exit 1
fi
#size=`wc -c ${file} | awk '{ printf("%08x", $1); }'`
size=`wc -c ${file} | awk '{ printf("%d", $1); }'`
size=$((${size} + (4 - (${size} % 4))))
tsize=`echo ${size} | awk '{ printf("%08x", $1); }'`
#####################################
printf "%b" \\x${tsize:6:2} >> ${out}
printf "%b" \\x${tsize:4:2} >> ${out}
printf "%b" \\x${tsize:2:2} >> ${out}
printf "%b" \\x${tsize:0:2} >> ${out}
for ((i=0; i<506; i++));
do
	printf "%b" \\x"00" >> ${out}
done
printf "%b" \\x"55" >> ${out}
printf "%b" \\x"aa" >> ${out}
cat ${file} >> ${out}
size=`wc -c ${file} | awk '{ printf("%d", $1); }'`
pad=$((16 - (${size} % 16)))
for ((i=0; i<pad; i++));
do
	printf "%b" \\x"00" >> ${out}
done
