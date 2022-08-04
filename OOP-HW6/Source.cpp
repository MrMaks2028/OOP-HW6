#include <iostream>
#include <string>

class Harvest {
public:
	Harvest() {}
	static int getAllHarvest() {
		return fruits + berries;
	}
	static int getAllCollectedHarvest() {
		return collectedHarvest;
	}
	static int fruits;
	static int berries;
	static int collectedHarvest;
};

class Plants {
public:
	Plants() {
		plantsCount++;
	}
	Plants(std::string name) : Plants() {
		_name = name;
	}
	~Plants() {
		plantsCount--;
	}
	void setName(std::string name) {
		_name = name;
	}
	std::string getName() {
		return _name;
	}
	static int getAllPlants() {
		return plantsCount;
	}
	static int plantsCount;
private:
	std::string _name;
};

class Trees : public Plants {
public:
	Trees() : Plants() {}
	Trees(std::string name, int harvestCount) : Plants(name) {
		_harvestCount = harvestCount;
		Harvest::fruits += _harvestCount;
	}
	int _harvestCount = 0;
};

class Bushes : public Plants {
public:
	Bushes() : Plants() {}
	Bushes(std::string name, int harvestCount) : Plants(name) {
		_harvestCount = harvestCount;
		Harvest::berries += _harvestCount;
	}
	int _harvestCount = 0;
};

class Fruits : public Harvest {
public:
	Fruits() {}
	static int collectHarvest(Trees& other, int harvest) {
		if (other._harvestCount == 0 || harvest > other._harvestCount)
			return 0;
		other._harvestCount -= harvest;
		fruits -= harvest;
		collectedHarvest += harvest;
		return fruits;
	}
};

class Berries : public Harvest {
public:
	Berries() {}
	static int collectHarvest(Bushes& other, int harvest) {
		if (other._harvestCount == 0 || harvest > other._harvestCount)
			return 0;
		other._harvestCount -= harvest;
		berries -= harvest;
		collectedHarvest += harvest;
		return berries;
	}
};

int Plants::plantsCount = 0;
int Harvest::fruits = 0;
int Harvest::berries = 0;
int Harvest::collectedHarvest = 0;

int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");

	Trees tree1("Apple Tree", 20);
	Trees tree2("Palm", 30);
	Bushes bush1("Strawberry", 15);
	Bushes bush2("Raspberry", 22);
	cout << "Кол-во всех растений: " << Plants::getAllPlants();
	cout << "\n\nДо сборки плодов:\n";
	cout << "\n\nКол-во оставшихся плодов: " << Harvest::getAllHarvest();
	cout << "\nКол-во собранных плодов: " << Harvest::getAllCollectedHarvest();
	Fruits::collectHarvest(tree1, 12);
	Fruits::collectHarvest(tree2, 28);
	Berries::collectHarvest(bush1, 5);
	Berries::collectHarvest(bush2, 20);
	cout << "\n\nПосле сборки плодов:\n";
	cout << "\nКол-во оставшихся плодов: " << Harvest::getAllHarvest();
	cout << "\nКол-во собранных плодов: " << Harvest::getAllCollectedHarvest();

	return 0;
}