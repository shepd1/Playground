#if defined(DEBUG) || defined(_DEBUG) || defined(__debug)

#include "MemMngr_shepd1.h";

Allocation* _first = 0;

void log() {
	Allocation* a = _first;
	int memoryLeaks = 0;
	int leakSize = 0;
	int maxMemoryUsed = 0;
	char buffer[100][100];
	int n = 0;
	
	if(_first) {
		while (a) {
			printf("#%-3i ", a->number);
			if (a->type == Single)
			{
				printf("%-16s", "operator new");
			}
			else
			{
				printf("%-16s", "operator new[]");
			}

			printf("%-8u", a->size);
			printf("0x%-20p", a->address);


			if (a->deallocation != Deallocated) {
				printf("!!NOT DEALLOCATED!!  ");
				if (a->deallocation == TypeMismatch) {
					printf("(Deallocation type mismatch)");
				}
				memoryLeaks++;
				leakSize += a->size;

				//NOTE(dave): Only capable printing the first 100 leaks under "Leaks at:" section
				if (n < 100) {
					snprintf(buffer[n], 100, "#%-4i 0x%-18p Size: %-8u", a->number, a->address, a->size);
				}
				n++;
			}

			maxMemoryUsed += a->size;

			printf("\n");
			a = a->next;
		}
	}
	else {
		std::cout << "No Allocation found... Nothing to log" << std::endl;
	}
	
	printf("\n**********************************************\n\n");
	printf("Number of leaks  : %i\n", memoryLeaks);
	printf("Total leaksize   : %i bytes\n", leakSize);
	printf("Total memory used: %i bytes\n", maxMemoryUsed);
	printf("\n\n");
	printf("Leaks at:\n");

	int i = 0;
	while (i<n) {
		printf(buffer[i]);
		printf("\n");
		i++;
	}
	getchar();
}

void allocate(size_t size, uint64_t address, AllocationType type) {
	Allocation* a = 0;
	uint32_t n = 1;

	if (!_first) {
		_first = (Allocation*) malloc(sizeof(Allocation));
		a = _first;
		std::atexit(log);
	} 
	else {
		a = _first;
		while (a->next) {
			a = a->next;
		}
		a->next = (Allocation*) malloc(sizeof(Allocation));
		n = a->number;
		a = a->next;
		n++;		
	} 

	*a = {};
	a->number = n;
	a->size = size;
	a->address = address;
	a->type = type;
	a->deallocation = NotDeallocated;
}

void deallocate(uint64_t address, AllocationType type) {
	Deallocation deallocation = NotDeallocated;
	Allocation* a = _first;

	while (a) {
		if (a->address == address) {
			break;
		}
		a = a->next;
	}

	if (a) {
		if (a->type != type) {
			deallocation = TypeMismatch;
		}
		else {
			deallocation = Deallocated;
		}
		
		a->deallocation = deallocation;
	}
}

void* operator new(size_t size) throw(std::bad_alloc()) {
	//std::cout << "New Single: " << size << std::endl;
	void* p = malloc(size);
	if (!p) throw std::bad_alloc();
	allocate(size, (uint64_t) p, Single);
	return p;
}
void* operator new[](size_t size) throw(std::bad_alloc()) {
	//std::cout << "New Array: " << size << std::endl;
	void* p = malloc(size);
	if (!p) throw std::bad_alloc();
	allocate(size, (uint64_t) p, Array);
	return p;
}
void operator delete(void *p) throw() {
	deallocate((uint64_t) p, Single);
	free(p);
}
void operator delete[](void *p) throw() { 
	deallocate((uint64_t)p, Array);
	free(p);
}

#endif