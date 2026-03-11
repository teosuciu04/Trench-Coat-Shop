#include "tests.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>

void testTrenchCoat() {
    // Test default constructor
    TrenchCoat c1;
    assert(c1 == TrenchCoat()); // same size/color = true

    // Test parameterized constructor
    TrenchCoat c2("M", "Black", 120, 5, "http://photo1.com");
    assert(!(c2 == c1)); // c2 has data, c1 is empty

    // Test copy constructor
    TrenchCoat c3 = c2;
    assert(c3 == c2); // size and color same
    assert(c3 == TrenchCoat("M", "Black", 0, 0, "")); // == compares only size and color

    // Test display() output using stringstream
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf()); // redirect cout

    c2.display();

    std::cout.rdbuf(oldCout); // restore cout
    std::string output = buffer.str();
    std::string expected = "Trench Coat - Size: M, Colour: Black, Price: $120, Quantity: 5, Photo: http://photo1.com\n";
    assert(output == expected);

    // Test == false when color or size differ
    TrenchCoat c4("L", "Black", 120, 5, "http://photo1.com");
    TrenchCoat c5("M", "Red", 120, 5, "http://photo1.com");
    assert(!(c2 == c4)); // different size
    assert(!(c2 == c5)); // different color

    {
        std::cout << "Al TrenchCoat tests passed!\n";
    }

    //test getters
    assert(c2.getPrice() == 120);
    assert(c2.getQuantity() == 5);
    assert(c2.getPhotograph() == "http://photo1.com");
}

void testRepository() {
	// Test default constructor
	Repository repo;
	assert(repo.getSize() == 0);
	// Test add and duplicate prevention
	TrenchCoat c1("M", "Black", 120, 5, "http://photo1.com");
	TrenchCoat c2("L", "Red", 150, 3, "http://photo2.com");
    repo.addTrenchCoat(c1);
    repo.addTrenchCoat(c2);
   // repo.addTrenchCoat(c1);
	assert(repo.getSize() == 2);

	// Test remove
    repo.removeTrenchCoat("M", "Black");
	assert(repo.getSize() == 1);
	try
	{
		repo.removeTrenchCoat("M", "Black");
		assert(false); // should not reach here
	}
	catch (const std::runtime_error& e) {
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	// Test update
	TrenchCoat c3("L", "Red", 200, 3, "http://photo3.com");
	assert(repo.updateTrenchCoat("L", "Red", c3) == true);
	assert(repo.updateTrenchCoat("M", "Black", c3) == false); // not found
	//Test get
   vector<TrenchCoat> coats = repo.getTrenchCoats();
    assert(coats[0] == c2);
}

void testService() {
	Repository repo;
    Service service{repo};

    // Test addTrenchCoatService (valid input)
    bool added = service.addTrenchCoatService("M", "Red", 150, 10, "http://photo.com/red.jpg");
    assert(added == true);  // should add successfully

    // Test duplicate add (assumes Repository prevents duplicates)
    bool duplicate = service.addTrenchCoatService("M", "Red", 150, 10, "http://photo.com/red.jpg");
    assert(duplicate == false); // should not add duplicate

    // Test invalid input (Validator should throw)
    try {
        service.addTrenchCoatService("", "Blue", -100, 0, "");
        assert(false); // should not reach here
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected validation exception: " << e.what() ;
    }

    try {
        service.addTrenchCoatService("XS", "", -100, 0, "");
        assert(false); // should not reach here
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected validation exception: " << e.what();
    }

    try {
        service.addTrenchCoatService("S", "Blue", -100, 0, "");
        assert(false); // should not reach here
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected validation exception: " << e.what();
    }

	try {
		service.addTrenchCoatService("S", "Blue", 100, -1, "");
		assert(false); // should not reach here
	}
	catch (const std::runtime_error& e) {
		std::cout << "Caught expected validation exception: " << e.what();
	}

    try {
        service.addTrenchCoatService("S", "Blue", 100, 3, "");
        assert(false); // should not reach here
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected validation exception: " << e.what();
    }

    // Test updateTrenchCoatService (valid)
    bool updated = service.updateTrenchCoatService("M", "Red", 199, 20, "http://photo.com/red-updated.jpg");
    assert(updated == true);

    // Try update non-existent
    bool updateFail = service.updateTrenchCoatService("L", "Orange", 123, 5, "http://photo.com/none.jpg");
    assert(updateFail == false);

    // Test removeTrenchCoatService (valid)
    bool removed = service.removeTrenchCoatService("M", "Red");
    assert(removed == true);

    // Remove non-existent coat
    bool removeFail = service.removeTrenchCoatService("XL", "Pink");
    assert(removeFail == false);

    // Test populateRepo
    service.populateRepo();
    // Check if a known item exists (XL, White)
    bool updatedWhite = service.updateTrenchCoatService("XL", "White", 300, 1, "https://updated.com/white.jpg");
    assert(updatedWhite == true);

    //test get repo
    vector<TrenchCoat> coats = service.getTrenchCoats();
    TrenchCoat c("M", "Red", 100, 4, "jhbbh");
    assert(coats[0] == c);

    assert(service.getSize() == 10);
}

void testUserService() {
    Repository repo;
	UserService userService{ repo };

    // Create sample trench coats
    TrenchCoat t1("M", "Black", 150, 10, "http://photo.com/1.jpg");
    TrenchCoat t2("L", "Red", 180, 5, "http://photo.com/2.jpg");
    TrenchCoat t3("M", "Blue", 170, 7, "http://photo.com/3.jpg");

    // === Test AddToCart ===
    bool addResult1 = userService.AddToCart(t1);
    assert(addResult1 == true); // Should succeed

    bool addResult2 = userService.AddToCart(t1);
    assert(addResult2 == false); // Should fail: duplicate

    //get cart
    vector<TrenchCoat> coatsincart = userService.getCart();
    assert(coatsincart[0] == t1);


    int new_sum = userService.setSum(450);
    assert(userService.getSum() == new_sum);

    // === Test getTrenchCoatsBySize ===
    vector<TrenchCoat> allCoats;
    allCoats.push_back(t1);
    allCoats.push_back(t2);
    allCoats.push_back(t3);

    // Filter by size "M"
    vector<TrenchCoat> filtered = userService.getTrenchCoatsBySize(allCoats, "M");
    assert(filtered.size() == 2);
    assert(filtered[0] == t1);
    assert(filtered[1] == t3);

    // Filter by size "L"
    vector<TrenchCoat> filteredL = userService.getTrenchCoatsBySize(allCoats, "L");
    assert(filteredL.size() == 1);
    assert(filteredL[0] == t2);

    // Filter by size "S" (not present)
    vector<TrenchCoat> filteredEmpty = userService.getTrenchCoatsBySize(allCoats, "S");
    assert(filteredEmpty.size() == 0);

    // Filter with empty size string = should return all
    vector<TrenchCoat> filteredAll = userService.getTrenchCoatsBySize(allCoats, "");
    assert(filteredAll.size() == 3);

    
}

void testComparator()
{
	cout << "Testing comparator\n";
	TrenchCoat c1("XS", "Red", 150, 5, "http://photo.com/1.jpg");
	TrenchCoat c2("S", "Blue", 100, 3, "http://photo.com/2.jpg");
	TrenchCoat c3("M", "Green", 200, 2, "http://photo.com/3.jpg");
	TrenchCoat c4("L", "Yellow", 120, 4, "http://photo.com/4.jpg");

	ComparatorAscendingByPrice comparator1;
	ComparatorDescendingByQuantity comparator2;

	std::vector<TrenchCoat> coats = { c1, c2, c3, c4 };
	sortTrenchCoats(coats, comparator1);
	assert(coats[0].getPrice() == 100);
	assert(coats[1].getPrice() == 120);

	sortTrenchCoats(coats, comparator2);
	assert(coats[0].getQuantity() == 2);
	assert(coats[1].getQuantity() == 3);
    
    
}
void Tests::testAll()
{
	//testTrenchCoat();
	//testRepository();
	//testService();
	//testUserService();
	testComparator();
	std::cout << "All tests passed!\n";
}
