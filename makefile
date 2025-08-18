# Program and compilation options
PROG = huffman
CC = gcc
OPTIONS = -Wall -Iinc

# List all .c source files and .o object files
SOURCES = $(wildcard src/*.c) # Use wildcard to find all .c files in src
OBJETS = $(SOURCES:src/%.c=obj/%.o) # Map source files to object files in obj

# Main rule - build the entire project
all: create_dir $(PROG)

# Create the directory for object files
create_dir:
	@mkdir -p obj

out_dir:
	@mkdir -p out

# Compile the final program
$(PROG): $(OBJETS)
	@echo "🔨 Building program $(PROG)..."
	$(CC) -o $(PROG) $(OBJETS) $(OPTIONS)
	@echo "✅ Program built successfully!"
	@echo " "

# Rule to compile each source file into an object file
obj/%.o: src/%.c
	@echo "🔄 Ensuring obj directory exists..."
	@mkdir -p obj
	@echo "📝 Compiling $<..."
	$(CC) $(OPTIONS) -c $< -o $@
	@echo "✅ $< compiled successfully!"
	@echo " "


# Run the program
run: $(PROG)
	@echo "🚀 Launching program $(PROG)..."
	./$(PROG)

# Clean compiled files
clean:
	@echo "🧹 Cleaning generated files..."
	rm -f obj/*.o $(PROG)
	rm -f out/*.dot out/*.pdf 2>/dev/null || true
	@echo "✨ Cleanup completed!"
	@echo " "

# Help - show available commands
help:
	@echo "Available commands:"
	@echo "  make all   - build the program"
	@echo "  make run   - run the program"
	@echo "  make clean - remove compiled files"
	@echo "  make help  - show this help"


# These are phony targets (names, not files)
.PHONY: all create_dir run clean help