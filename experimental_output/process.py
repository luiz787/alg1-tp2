import csv

def main():
	print('hey')
	for i in range(100, 1001, 100):
		file_name = "{}.out".format(i)
		print(file_name)
		gulosos = []
		dinamicos = []
		with open(file_name) as file:
			for _ in range(0, 100):
				file.readline()
				file.readline()
				gulosos.append(file.readline().split(' ')[-1].rstrip())
				dinamicos.append(file.readline().split(' ')[-1].rstrip())
		
		with open('output{}.csv'.format(i), 'w') as csvfile:
			zipped = list(zip(gulosos, dinamicos))
			wr = csv.writer(csvfile, dialect='excel', lineterminator='\n')
			wr.writerow(["Tempo guloso", "Tempo programacao dinamica"])
			wr.writerows(zipped)

if __name__ == "__main__":
	main()