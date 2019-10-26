import sys

def main():
	size = int(sys.argv[1])
	lines = [("{} {}".format(i * 10, i)) for i in range(size, 0, -1)]
	max_amount = size * 10
	print(str(max_amount) + " " + str(size))
	lines[0] = "{} {}".format(size * 10, size + 1)
	for line in lines:
		print(line)


if __name__ == '__main__':
	main()