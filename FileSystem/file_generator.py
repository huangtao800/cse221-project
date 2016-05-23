# Helper function to generate random data filled test file
from random import randrange
import numpy

array = [2, 4, 8, 16, 32, 64, 128]
#array = [1, 2, 3]
array = [0, 1, 2, 3, 4, 5, 6]


for x in array:

  fp = open("size64k_%s" % x, "w+")

  content = numpy.random.bytes(64*1024)

  fp.write(content);
  fp.close()