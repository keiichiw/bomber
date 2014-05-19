rm -f ./data/result.txt
cp ./data/initialBoard.txt ./data/input.txt
echo "Start Simulation"
java -cp ./Sim/bin Simu
rm -f ./data/input.txt ./Sim/temp/*

