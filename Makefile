# simple make file used to compile project 1 database from source files

# List needed object files here...
OBJS = course.o databaseMain.o inputFunctions.o

# Target executable
TARGET = database

# Rule for building executable from object files (link step)
database: $(OBJS)
	g++ -o $(TARGET) $(OBJS)

# Rule for building object files from cpp files
%.o: %.cpp
	g++ -c -g -Wall -o $@ $<

# make clean to get rid of all object  and executables
clean:
	rm $(OBJS)
	rm $(TARGET)
