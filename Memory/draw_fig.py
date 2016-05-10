import matplotlib.pyplot as plt
import math

sizeList = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288]
strideList = [4, 16, 64, 128, 1024, 2048, 1048576, 2097152, 4194304]


def getStride(s):
	if s < 1024:
		return str(s) + "B"
	elif s < 1024*1024:
		return str(s/1024) + "KB"
	else:
		return str(s/1024/1024) + "MB"

time = []
for l in open("ram_output.txt"):
	line = l.split()
	time.append(eval(line[len(line)-1]) - 8)

pos = 0
x = []
for s in sizeList:
	x.append(math.log(s*1024, 2))


plt.figure(1)

for stride in strideList:
	y = []
	for i in range(len(sizeList)):
		y.append(time[pos]);
		pos += 1
	plt.subplot(111)
	plt.plot(x, y, label=getStride(stride))
plt.legend(bbox_to_anchor=(0., 0.65, 0.65, .102), loc=3,
           ncol=2, borderaxespad=0.)

plt.xlabel('Log of memory region size')
plt.ylabel("Cycles")

plt.annotate('32 KB L1 cache', xy=(14, 10), xytext=(13, 100),
            arrowprops=dict(facecolor='black', shrink=0.1),
            )

plt.annotate('256 KB L2 cache', xy=(17, 20), xytext=(17, 150),
            arrowprops=dict(facecolor='black', shrink=0.1),
            )
plt.show()

