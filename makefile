OBJ := main.o cashier.o good.o supermarket.o customer.o
  
supermarket : $(OBJ)  
	g++ -o supermarket $(OBJ) -lpthread

.PHONY: clean   
clean:
	rm -f $(OBJ)