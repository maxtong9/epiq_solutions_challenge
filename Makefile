CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC_DIR = src

all:  
	$(CXX) $(SRC_DIR)/*.cpp -o challenge_1

clean:
	rm -rf challenge_1