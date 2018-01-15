#include "testslib.hpp"

#include "room.hpp"

#include "ArtificialHouseplant.hpp"
#include "FloweringHousplant.hpp"
#include "FoliarHouseplant.hpp"
#include "FloweringHousplant.hpp"
#include "FruitingHouseplant.hpp"

#include "SplitControl.hpp"

#include "messages.hpp"

DateTime & TODAY = CurrentDate::Instance().getCurrentDate();

DECLARE_OOP_TEST(Flowering_plants_test_wrong_cases)
{
	ASSERT_THROWS(FloweringHouseplant r("lemon tree", 10, 3, 0, 5)
		, Messages::WrongFloweringDays);
	ASSERT_THROWS(FloweringHouseplant r("lemon tree", 10, 3, 1000, 5)
		, Messages::WrongFloweringDays);
	ASSERT_THROWS(FloweringHouseplant r("lemon tree", 10, 3, 10, -20)
		, Messages::WrongWateringCount);
	ASSERT_THROWS(FloweringHouseplant r("lemon tree", 10, 3, 1, 0)
		, Messages::WrongWateringCount);
}

DECLARE_OOP_TEST(Flowering_plants_test_without_flowering)
{
	FloweringHouseplant r("lemon tree", 10, 3, 30, 5);
	assert(r.getCurrentRightWatering() == 0);
	assert(r.getName() == "lemon tree");
	assert(r.getType() == Houseplant::FLOWERING);

	r.GiveWater();
	assert(TODAY == DateTime(2016, 1));
	assert(r.getCurrentRightWatering() == 0);

	for (int i = 0; i < 3; i++)
		r.DayGone();

	assert(TODAY == DateTime(2016, 4));
	r.GiveWater();

	assert(r.getCurrentRightWatering() == 1);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Flowering_plants_test_with_many_watering)
{
	FloweringHouseplant r("lemon tree", 10, 5, 30, 5);
	r.GiveWater();
	assert(TODAY == DateTime(2016, 1));
	assert(r.getCurrentRightWatering() == 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
			r.DayGone();
		r.GiveWater();
	}

	assert(r.getLastWateringDate() == DateTime(2016, 16));
	assert(TODAY == DateTime(2016, 16));
	assert(r.getCurrentRightWatering() == 3);
	
	r.GiveWater();

	assert(TODAY == DateTime(2016, 16));
	assert(r.getCurrentRightWatering() == 2);

	for (int j = 0; j < 2; j++)
		r.DayGone();

	r.GiveWater();

	assert(TODAY == DateTime(2016, 18));
	assert(r.getCurrentRightWatering() == 1);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Flowring_plants_test_with_not_success_flowering)
{
	FloweringHouseplant r("lemon tree", 10, 2, 30, 10);

	for (int i = 0; i < 9; i++)
	{
		r.DayGone();
		r.DayGone();

		r.GiveWater();
	}

	assert(r.getCurrentRightWatering() == 9);
	assert(r.getStatus() == FloweringHouseplant::STATUS::NOT_ENAUGH_WATERING);
	r.DayGone();
	r.DayGone();
	r.GiveWater();
	assert(r.getCurrentRightWatering() == 10);
	assert(r.getStatus() == FloweringHouseplant::STATUS::FLOWERING);

	for (int i = 0; i < 7; i++)
	{
		r.DayGone();
		r.DayGone();
		r.GiveWater();
	}
	assert(r.getCurrentFloweringDays() == 7);
	assert(r.getStatus() == FloweringHouseplant::STATUS::FLOWERING);

	r.GiveWater();
	assert(r.getCurrentFloweringDays() == 0);
	assert(r.getStatus() == FloweringHouseplant::STATUS::NOT_ENAUGH_WATERING);
}

DECLARE_OOP_TEST(Flowering_plants_test_with_success_flowering)
{
	FloweringHouseplant r("lemon tree", 10, 2, 25, 10);

	for (int i = 0; i < 10; i++)
	{
		r.DayGone();
		r.DayGone();
		r.GiveWater();
	}
	assert(r.getCurrentRightWatering() == 10);
	assert(r.getStatus() == FloweringHouseplant::STATUS::FLOWERING);

	assert(r.getFlowering() == 25);

	for (int i = 0; i < 24; i++)
	{
		r.DayGone();
		r.DayGone();
		r.GiveWater();
	}	
	assert(r.getCurrentFloweringDays() == 24);

	r.DayGone();
	r.DayGone();
	r.GiveWater();

	assert(r.getCurrentRightWatering() == 0);
	assert(r.getCurrentFloweringDays() == 0);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Flowring_plants_test_with_breaking_flowering)
{
	FloweringHouseplant r("lemon tree", 10, 2, 15, 10);

	for (int i = 0; i < 10; i++)
	{
		r.DayGone();
		r.DayGone();
		r.GiveWater();
	}

	assert(r.getCurrentRightWatering() == 10);
	assert(r.getStatus() == FloweringHouseplant::STATUS::FLOWERING);

	for (int i = 0; i < 10; i++)
	{
		r.DayGone();
		r.DayGone();
		r.GiveWater();
	}
	assert(r.getCurrentFloweringDays() == 10);
	assert(r.getStatus() == FloweringHouseplant::STATUS::FLOWERING);

	for (int i = 0; i < 5; i++)
		r.DayGone();

	r.GiveWater();
	assert(r.getCurrentFloweringDays() == 0);
	assert(r.getCurrentRightWatering() == 0);
	assert(r.getPeriod() == 2);
	assert(r.getStatus() == FloweringHouseplant::STATUS::NOT_ENAUGH_WATERING);
	assert(r.getLastWateringDate() == DateTime(2016, 56));

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Fruiting_plants_test_wrong_cases)
{
	ASSERT_THROWS(FruitingHouseplant r("Lemon tree", 50, 1, 40, 100, "", 5)
		, "Empty fruit name");
	ASSERT_THROWS(FruitingHouseplant r("Lemon tree", 50, 1, 40, 100, "fruit", -5)
		, Messages::UnexpectedFruiting);
	ASSERT_THROWS(FruitingHouseplant r("Lemon tree", 50, 1, 40, 100, "name", 0)
		, Messages::UnexpectedFruiting);
}

DECLARE_OOP_TEST(FruitingHouseplant_test_not_success_fruiting)
{
	FruitingHouseplant r("Lemon tree", 50, 1, 40, 100, "lemon", 5);
	assert(r.getName() == "Lemon tree");
	assert(r.getAge() == 50);
	assert(r.getNeedRightWatering() == 100);
	assert(r.getPeriod() == 1);
	assert(r.getFlowering() == 40);
	assert(r.getFruitName() == "lemon");
	assert(r.getFruitingDays() == 5);
	assert(r.getType() == Houseplant::FRUIT);


	for (int i = 0; i < 101; i++)
	{
		r.DayGone();
		r.GiveWater();
	}
	for (int i = 0; i < 40; i++)
	{
		r.DayGone();
		r.GiveWater();
	}

	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			r.DayGone();

		r.GiveWater();
	}
	assert(r.getCurrentFruitingDays() == 3);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(FruitingHouseplant_test_success_fruiting)
{
								//age period flowering needwatering 
	FruitingHouseplant r("Lemon tree", 23, 10, 5, 3, "limonchik", 50);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
			r.DayGone();

		r.GiveWater();
	}

	assert(r.getStatus() == FloweringHouseplant::FLOWERING);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
			r.DayGone();

		r.GiveWater();
	}

	assert(r.getPeriod() == 12);

	for (int i = 0; i < 49; i++)
	{
		for (int j = 0; j < 12; j++)
			r.DayGone();
		r.GiveWater();
	}

	assert(r.getCurrentFruitingDays() == 49);
	assert(TODAY == DateTime(2017, 359));

	for (int j = 0; j < 12; j++)
		r.DayGone();
	r.GiveWater();
	
	assert(TODAY == DateTime(2018, 8));
	assert(r.getCurrentFruitingDays() == 0);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(FruitingHouseplant_test_continue_fruiting)
{
	//								age period flowering needwatering 
	FruitingHouseplant r("Lemon tree", 23, 10, 5, 3, "limonchik", 50);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
			r.DayGone();

		r.GiveWater();
	}

	assert(r.getStatus() == FloweringHouseplant::FLOWERING);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
			r.DayGone();

		r.GiveWater();
	}

	assert(r.getPeriod() == 12);

	for (int i = 0; i < 49; i++)
	{
		for (int j = 0; j < 12; j++)
			r.DayGone();
		r.GiveWater();
	}

	assert(r.getCurrentFruitingDays() == 49);

	r.DayGone();
	r.GiveWater();

	assert(r.getCurrentFruitingDays() == 49);
	assert(r.getCurrentFloweringDays() == 0);

	for (int i = 0; i < 49; i++)
	{
		for (int j = 0; j < 12; j++)
			r.DayGone();
		r.GiveWater();
	}
	
	r.GiveWater();

	assert(r.getCurrentFruitingDays() == 0);
	TODAY.dateReset();
}

DECLARE_OOP_TEST(ArtificialHouseplant_test)
{
	ArtificialHouseplant m("Masha", 18);

	assert(m.getAge() == 18);
	assert(m.getName() == "Masha");
	assert(m.getPeriod() == 0);
	
	assert(m.getType() == Houseplant::ARTIFICIAL);

	m.DayGone();

	assert(TODAY == DateTime(2016, 2));

	TODAY.dateReset();
}

DECLARE_OOP_TEST(ArtificialHouseplant_try_to_watering_test)
{
	ArtificialHouseplant m("rose", 18);

	ASSERT_THROWS(m.GiveWater(), "Sorry, it's useless!");
}

DECLARE_OOP_TEST(FoliarHouseplant_test_wrong_case)
{
	SpliterHelper spliter;
	
	ASSERT_THROWS(FoliarHouseplant s("test", 20, 2, 0, spliter)
		, Messages::UnexpectedHeight);
	ASSERT_THROWS(FoliarHouseplant s("test", 20, 2, -120, spliter)
		, Messages::UnexpectedHeight);
	ASSERT_THROWS(FoliarHouseplant s("test", 20, 2, 250, spliter)
		, Messages::UnexpectedHeight);
	ASSERT_THROWS(FoliarHouseplant s("test", 20, 2, 2500, spliter)
		, Messages::UnexpectedHeight);
}

DECLARE_OOP_TEST(FoliarHouseplant_test_without_split)
{
	SpliterHelper spliter;
	FoliarHouseplant s("test", 20, 2, 200, spliter);
	assert(s.getName() == "test");
	assert(s.getAge() == 20);
	assert(s.getPeriod() == 2);
	assert(s.getHeight() == 200);

	for (int i = 0; i < 20; i++)
	{
		s.DayGone();
		s.DayGone();
		s.GiveWater();
	}

	assert(s.getHeight() == 220);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(FoliarHouseplant_test_with_split)
{
	SpliterHelper spliter;
	FoliarHouseplant s("test", 20, 2, 249, spliter);

	Room university;
	spliter.connectToRoom(&university);

	s.DayGone();
	s.DayGone();
	s.GiveWater();	

	auto buf = university.getPlant(0);

	assert(s.getHeight() == 125);
	assert(buf);
		
	FoliarHouseplant * d = dynamic_cast<FoliarHouseplant *>(buf);
	assert(d->getHeight() == 125);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(FoliarHouseplant_test_with_split_wrong_cases)
{
	SpliterHelper spliter;
	FoliarHouseplant s("test", 20, 2, 249, spliter);

	ASSERT_THROWS(spliter.connectToRoom(nullptr), Messages::WrongPointerToRoom);
	ASSERT_THROWS(SpliterHelper(nullptr), Messages::WrongPointerToRoom);
}

DECLARE_OOP_TEST(Room_abilitys_testing_1)
{
	Room a;

	assert(a.getPlantsCount() == 0);
	a.addNewHousplant(new FloweringHouseplant("CUCUMBER", 10, 2, 25, 10));
	assert(a.getPlantsCount() == 1);
	a.addNewHousplant(new FruitingHouseplant("Roze", 50, 1, 40, 100, "lemon", 5));
	assert(a.getPlantsCount() == 2);

	std::vector<std::string> plants;
	for (auto const & x : a.iterable_plants())
		plants.push_back(x->getName());

	assert(plants.size() == 2);
	assert(plants[0] == "CUCUMBER");
	assert(plants[1] == "Roze");
}

DECLARE_OOP_TEST(Room_abilitys_testing_2)
{
	Room a;
	SpliterHelper spliter;
	spliter.connectToRoom(&a);

	assert(a.isEmpty());

	a.addNewHousplant(new FoliarHouseplant("test", 20, 2, 249, spliter));

	auto foliar = a.getPlant(0);
	
	assert(foliar);
	FoliarHouseplant * d = dynamic_cast<FoliarHouseplant *>(foliar);
	d->DayGone();
	assert(TODAY != d->getLastWateringDate());
	d->GiveWater();
	assert(d->getLastWateringDate() == TODAY);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Room_abilitys_testing_3)
{
	Room a;
	SpliterHelper spliter;

	assert(a.isEmpty());

	a.addNewHousplant(new FloweringHouseplant("BMW", 10, 2, 25, 10));
	a.addNewHousplant(new FruitingHouseplant("LOTUS", 50, 1, 40, 100, "lemon", 5));
	a.addNewHousplant(new ArtificialHouseplant("BUTTON", 50));
	a.addNewHousplant(new FoliarHouseplant("CAST", 20, 2, 249, spliter));
	a.addNewHousplant(new ArtificialHouseplant("magic", 20));

	assert(a.getPlantsCount() == 5);

	auto foliar = a.getPlant(3);
	auto flower = a.getPlant(0);
	auto fruit = a.getPlant(1);
	auto art_1 = a.getPlant(2);
	auto art_2 = a.getPlant(4);

	assert(flower);
	assert(foliar);
	assert(fruit);
	assert(art_1);
	assert(art_2);

	FoliarHouseplant * fol = dynamic_cast<FoliarHouseplant *>(foliar);
	assert(fol);
	FloweringHouseplant * flow = dynamic_cast<FloweringHouseplant *>(flower);
	assert(flow);
	ArtificialHouseplant * a_1 = dynamic_cast<ArtificialHouseplant *>(art_1);
	assert(a_1);
	ArtificialHouseplant * a_2 = dynamic_cast<ArtificialHouseplant *>(art_2);
	assert(a_2);
	FruitingHouseplant * ft= dynamic_cast<FruitingHouseplant *>(fruit);
	assert(fruit);
}

DECLARE_OOP_TEST(Room_only_one_plant_testing)
{
	Room a;
	SpliterHelper spliter;
	
	a.addNewHousplant(new FloweringHouseplant("CUCUMBER", 10, 2, 25, 10));
	a.addNewHousplant(new FruitingHouseplant("Roze", 50, 1, 40, 100, "lemon", 5));
	a.addNewHousplant(new ArtificialHouseplant("Roze", 50));
	a.addNewHousplant(new FoliarHouseplant("test", 20, 2, 249, spliter));
	
	spliter.connectToRoom(&a);

	auto foliar = a.getPlant(3);

	assert(foliar);

	FoliarHouseplant * d = dynamic_cast<FoliarHouseplant *>(foliar);

	assert(d->getHeight() == 249);

	d->DayGone();
	d->DayGone();
	d->GiveWater();

	assert(a.getPlantsCount() == 5);

	auto foliarCopy = a.getPlant(4);

	assert(foliarCopy);

	FoliarHouseplant * d_1 = dynamic_cast<FoliarHouseplant *>(foliarCopy);

	assert(d_1->getHeight() == 125);
	assert(d_1->getName() == "test_copy");
	assert(d_1->getPeriod() == 2);

	for (int i = 0; i < 125; i++)
	{
		d_1->DayGone();
		d_1->DayGone();
		d_1->GiveWater();
	}

	assert(d_1->getLastWateringDate() == TODAY);
	assert(a.getPlant(2)->getLastWateringDate() == DateTime(2016, 1));
	assert(a.getPlant(1)->getLastWateringDate() == DateTime(2016, 1));
	assert(a.getPlant(0)->getLastWateringDate() == DateTime(2016, 1));

	auto copy_of_copy = a.getPlant(5);

	assert(copy_of_copy);

	FoliarHouseplant * d_2 = dynamic_cast<FoliarHouseplant *>(copy_of_copy);

	assert(d_2->getHeight() == 125);
	assert(d_2->getName() == "test_copy_copy");
	assert(d_2->getPeriod() == 2);

	assert(a.getPlantsCount() == 6);

	TODAY.dateReset();
}

DECLARE_OOP_TEST(Room_only_one_plant_testing_2)
{
	Room a;
	SpliterHelper spliter(&a);

	a.addNewHousplant(new FloweringHouseplant("CUCUMBER", 10, 2, 25, 5));
	a.addNewHousplant(new FloweringHouseplant("Tomatik", 10, 30, 5, 5));
	a.addNewHousplant(new FloweringHouseplant("Albina", 10, 15, 1, 2));
	a.addNewHousplant(new FloweringHouseplant("Intel", 10, 1, 25, 25));

	assert(a.getPlantsCount() == 4);

	auto first = a.getPlant(0);
	FloweringHouseplant * f = dynamic_cast<FloweringHouseplant*>(first);

	for (int i = 0; i < 5; i++)
	{
		f->DayGone();
		f->DayGone();
		f->GiveWater();
	}
	
	assert(f->getStatus() == FloweringHouseplant::FLOWERING);
	assert(f->getCurrentRightWatering() == 5);

	for (int i = 0; i < 25; i++)
	{
		f->DayGone();
		f->DayGone();
		f->GiveWater();
	}

	assert(f->getPeriod() == 4);

	for (int i = 0; i < 5; i++)
	{
		for(int i = 0; i < 4; i++)
			f->DayGone();
		
		f->GiveWater();
	}

	for (int i = 0; i < 25; i++)
	{
		for (int i = 0; i < 4; i++)
			f->DayGone();
		f->GiveWater();
	}

	assert(f->getPeriod() == 6);

	auto second = a.getPlant(2);
	FloweringHouseplant * s = dynamic_cast<FloweringHouseplant*>(second);

	s->GiveWater();

	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 15; i++)
			s->DayGone();
		s->GiveWater();
	}

	assert(s->getStatus() == FloweringHouseplant::FLOWERING);
	assert(s->getCurrentRightWatering() == 2);

	for (int i = 0; i < 15; i++)
		s->DayGone();

	s->GiveWater();
	

	assert(s->getPeriod() == 17);

	TODAY.dateReset();
}