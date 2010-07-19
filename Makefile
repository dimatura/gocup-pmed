CXX=g++
CXXFLAGS=-Wall -O2 -DNDEBUG -ffast-math -fomit-frame-pointer -fno-rtti
#CXXFLAGS=-Wall -g 

.PHONY: all
all: pmedian

pmedian:\
    pmedian.o\
    pmedproblem.o\
    vshop.o\
    pmedsolver.o\
    hillclimber.o\
    glhillclimber.o\
    sampleinitializer.o\
    utils.o\
    distancematrix.o\
    solution.o\
    options.o\
    lineiterator.o\
    dataloader.o
	$(CXX) $^ $(CXXFLAGS) -o $@

pmedian.o: pmedian.cc
	$(CXX) $(CXXFLAGS) -c $< 

pmedsolver.o: pmedsolver.cc
	$(CXX) $(CXXFLAGS) -c $< 

pmedproblem.o: pmedproblem.cc
	$(CXX) $(CXXFLAGS) -c $< 

hillclimber.o: hillclimber.cc
	$(CXX) $(CXXFLAGS) -c $< 

glhillclimber.o: glhillclimber.cc
	$(CXX) $(CXXFLAGS) -c $< 

vshop.o: vshop.cc
	$(CXX) $(CXXFLAGS) -c $< 

sampleinitializer.o: sampleinitializer.cc
	$(CXX) $(CXXFLAGS) -c $< 

utils.o: utils.cc
	$(CXX) $(CXXFLAGS) -c $< 

distancematrix.o: distancematrix.cc
	$(CXX) $(CXXFLAGS) -c $< 

options.o: options.cc
	$(CXX) $(CXXFLAGS) -c $< 

solution.o: solution.cc
	$(CXX) $(CXXFLAGS) -c $< 

dataloader.o: dataloader.cc
	$(CXX) $(CXXFLAGS) -c $< 

lineiterator.o: lineiterator.cc
	$(CXX) $(CXXFLAGS) -c $< 

# eda.o: eda.cc
# 	$(CXX) $(CXXFLAGS) -c $< 

.PHONY: clean
clean: 
	rm -f *.o pmedian
