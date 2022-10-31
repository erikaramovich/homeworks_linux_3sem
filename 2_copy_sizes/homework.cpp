#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

// function to calculate physical size
int physical_size(int fd){

	// physical size = 0
	int size = 0;

	// cursor is on the first position
	size = lseek(fd, 0, SEEK_SET);

	// cursor is on the last position
	size = lseek(fd, 0, SEEK_END);

	// check for issues
	if(size < 0){
		exit(errno);
	}

	// bringing cursor on the first position
	lseek(fd, 0, SEEK_SET);

	return size;
}


int logical_size(int fd){

	// logical size = 0
	int logic_size = 0;

	int start = 0;
	int end =0;

	// setting cursor on the first position
	int pos = lseek(fd, 0, SEEK_SET);

	// runing until the end to calculate data bytes
	while(pos != lseek(fd, 0, SEEK_END)){

		// setting cursor on the nearest data
		pos = lseek(fd, 0, SEEK_DATA);

		// check for issues
		if(pos < 0){
			exit(errno);
		}

		// saving the start of the data
		start = pos;

		// setting cursor on the nearest hole, where data ends
		pos = lseek(fd, 0, SEEK_HOLE);

		// check for issues
		if(pos < 0){
			exit(errno);
		}

		// saving the end of the data
		end = pos;

		// data_size = (end - start)

		// adding the data size to logic_size
		logic_size += (end - start);
	}

	// bringing cursor on the first position
	lseek(fd, 0, SEEK_SET);

	return logic_size;
}


int main(int argc, char **argv){

	// checking arguments
	if(argc < 3){
		std::cerr << "arguments are not enough" << std::endl;
		return 1;
	}

	// saving source and destination paths
	const char* source = argv[1];
	const char* destination = argv[2];

	// opening source path
	int source_fd = open(source, O_RDONLY);

	// checking for issues
	if(source_fd < 0){
		exit(errno);
	}

	// opening destination path
	int destination_fd = open(destination, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	// checking for issues
	if(destination_fd < 0){
		exit(errno);
	}

	std::cout << "Physical size of the source file: " << physical_size(source_fd) << std::endl;
	std::cout << "Logical size of the source file: " << logical_size(source_fd) << std::endl;

	std::cout << "Physical size of the destination file: " << physical_size(destination_fd) << std::endl;
	std::cout << "Logical size of the destination file: " << logical_size(destination_fd) << std::endl;

	// creating buffer
	char buffer[4096];

	while(true){

		int count = read(source_fd, buffer, 4096);

		if(count == 0){
			break;
		}

		if(count < 0){
			return 1;
		}

		int write_count = write(destination_fd, buffer, count);

		if(write_count < 0){
			exit(errno);
		}

	}

	std::cout << "AFTER COPY" << std::endl;
        std::cout << "Physical size of the source file: " << physical_size(source_fd) << std::endl;
        std::cout << "Logical size of the source file: " << logical_size(source_fd) << std::endl;

        std::cout << "Physical size of the destination file: " << physical_size(destination_fd) << std::endl;
        std::cout << "Logical size of the destination file: " << logical_size(destination_fd) << std::endl;


	close(source_fd);

	close(destination_fd);

	return 0;
}
