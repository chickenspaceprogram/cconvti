import numpy
array = numpy.random.rand(10000, 10000)

numpy.savetxt('bigarray.csv', array, delimiter=',')jlj