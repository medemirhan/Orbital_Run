#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "../Orbital_Run/type_definitions.h"
#include "../Orbital_Run/CEntity.h"
#include "../Orbital_Run/COrbitron.h"
#include "../Orbital_Run/CBomb.h"
#include "../Orbital_Run/CConfigurationData.h"
//#include "../Orbital_Run/CController.h"
//#include "../Orbital_Run/CControllerMainMenu.h"
//#include "../Orbital_Run/CControllerConfigMenu.h"
//#include "../Orbital_Run/CControllerPlayingScreen.h"
#include "../Orbital_Run/CModel.h"

#define EPSILON static_cast<FP32>(1e-10)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CEntityTests)
	{
	public:

		/* Tests Init() function of CEntity */
		TEST_METHOD(InitializationTest)
		{
			E_ENTITY_TYPES entity_type = ENTITY_TYPES_BOMB;
			FP32 x_pos = 0.0f;
			FP32 y_pos = 0.0f;
			FP32 velocity = 3.0f;
			FP32 radius = 10.0f;
			FP32 angle = 5.0f;
			INT32S orbit = 0.0f;
			INT32S num_life = 1;
			BOOLEAN is_alive = true;
			CBomb* p_bomb = DBG_NEW CBomb(entity_type, x_pos, y_pos, velocity, radius, angle, orbit, num_life, is_alive);
			Assert::AreEqual(static_cast<INT32S>(entity_type), static_cast<INT32S>(p_bomb->GetEntityType()));
			Assert::AreEqual(x_pos, p_bomb->GetPositionX(), EPSILON);
			Assert::AreEqual(y_pos, p_bomb->GetPositionY(), EPSILON);
			Assert::AreEqual(velocity, p_bomb->GetVelocity(), EPSILON);
			Assert::AreEqual(radius, p_bomb->GetRadius(), EPSILON);
			Assert::AreEqual(angle, p_bomb->GetAngle(), EPSILON);
			Assert::AreEqual(orbit, p_bomb->GetOrbit());
			Assert::AreEqual(num_life, p_bomb->GetNumLife());
			Assert::AreEqual(is_alive, p_bomb->GetIsAlive());
			delete p_bomb;
		}

		/* Tests RotateEntity() function of CEntity */
		TEST_METHOD(RotateEntityTest) // bunlarý fonksiyon haline getirip limitlerdeki inputlar ile çaðýrabilirsin.
		{
			CBomb* p_bomb = DBG_NEW CBomb(ENTITY_TYPES_BOMB, 0.0f, 0.0f, 5.0f, 10.0f, 1.0f, 0, 1, true);
			FP32 x_pivot = 0.0f, y_pivot = 0.0f;
			FP32 expected_angle = 6.0f;
			p_bomb->RotateEntity(x_pivot, y_pivot);
			Assert::AreEqual(expected_angle, p_bomb->GetAngle(), EPSILON);
			delete p_bomb;
		}
	};

	TEST_CLASS(COrbitronTests)
	{
	public:

		/* Tests ChangeOrbit() function of COrbitron */
		TEST_METHOD(ChangeOrbitTest)
		{
			COrbitron* p_orbitron = DBG_NEW COrbitron;
			INT32S orbit = 5;
			p_orbitron->SetOrbit(orbit);
			FP32 direction = -1.0f;
			p_orbitron->ChangeOrbit(direction);
			Assert::AreEqual(static_cast<INT32S>(orbit + direction), p_orbitron->GetOrbit());
			orbit = p_orbitron->GetOrbit();
			direction = +1.0f;
			p_orbitron->ChangeOrbit(direction);
			Assert::AreEqual(static_cast<INT32S>(orbit + direction), p_orbitron->GetOrbit());
			delete p_orbitron;
		}
	};

	TEST_CLASS(CConfigurationDataTests)
	{
	public:

		/* Tests exception handling of XMLParser() function of CConfigurationData */
		TEST_METHOD(ExceptionHandlingTest)
		{
			std::string filename1 = "config_no_file.xml";
			std::string filename2 = "config_corrupted.xml";
			std::wstring error = (L"ConfigFileErrorStatus is FALSE. It was expected to be TRUE.");

			CConfigurationData* p_config_data1 = DBG_NEW CConfigurationData(filename1);
			if (!p_config_data1->GetConfigFileErrorStatus()) {
				Assert::Fail(error.c_str());
			}else {

			}
			CConfigurationData* p_config_data2 = DBG_NEW CConfigurationData(filename2);
			if (!p_config_data2->GetConfigFileErrorStatus()) {
				Assert::Fail(error.c_str());
			}
			else {

			}
			delete p_config_data1, p_config_data2;
		}

		/* Tests XMLParser() function of CConfigurationData */
		TEST_METHOD(DataParsingTest)
		{
			std::string filename = "config_unittest.xml";
			CConfigurationData* p_config_data = DBG_NEW CConfigurationData(filename);

			Assert::AreEqual(filename, p_config_data->GetFilename());
			Assert::AreEqual((BOOLEAN)false, p_config_data->GetConfigFileErrorStatus());
			Assert::AreEqual(0.5f, p_config_data->GetOrbitronInitialVelocity(), EPSILON);
			Assert::AreEqual(0.51f, p_config_data->GetMonsterInitialVelocity(), EPSILON);
			Assert::AreEqual(2.5f, p_config_data->GetRocketOrbitronVelocityRatio(), EPSILON);
			Assert::AreEqual(0.03f, p_config_data->GetVelocityIncreaseAtLevelUp(), EPSILON);
			Assert::AreEqual(1.5f, p_config_data->GetMonsterOrbitChangeIntervalSec(), EPSILON);
			Assert::AreEqual(5.0f, p_config_data->GetMonsterSleepTimeSec(), EPSILON);
			Assert::AreEqual(3, p_config_data->GetOrbitronInitialLife());
			Assert::AreEqual(7, p_config_data->GetOrbitNumber());
			Assert::AreEqual(10, p_config_data->GetMonsterNumber());
			Assert::AreEqual(3, p_config_data->GetConstantLifeNumber());
			Assert::AreEqual(6, p_config_data->GetConstantBombAdditionNumber());
			Assert::AreEqual(10, p_config_data->GetRocketRightIntervalSec());
			Assert::AreEqual(15, p_config_data->GetBombAdditionIntervalSec());
			Assert::AreEqual(20, p_config_data->GetBombRemovalIntervalSec());
			Assert::AreEqual(3, p_config_data->GetLittlelifeNumForLife());
			Assert::AreEqual(p_config_data->GetOrbitronInitialVelocity(), p_config_data->GetOrbitronVelocity(), EPSILON);
			Assert::AreEqual(p_config_data->GetMonsterInitialVelocity(), p_config_data->GetMonsterVelocity(), EPSILON);
			Assert::AreEqual(p_config_data->GetOrbitronInitialVelocity() / VDEFAULT_ENTITTY_VBOMB_RATIO, p_config_data->GetBombVelocity(), EPSILON);
			Assert::AreEqual(p_config_data->GetOrbitronVelocity() * p_config_data->GetRocketOrbitronVelocityRatio(), p_config_data->GetRocketVelocity(), EPSILON);
			Assert::AreEqual(DEFAULT_ROCKETRIGHT_VELOCITY, p_config_data->GetRocketrightVelocity(), EPSILON);
			Assert::AreEqual(p_config_data->GetOrbitronInitialVelocity() / VDEFAULT_ENTITTY_VLIFE_RATIO, p_config_data->GetLifeVelocity(), EPSILON);
			delete p_config_data;
		}
	};

	TEST_CLASS(CModelTests)
	{
	public:

		/* Tests default constructor of CModel */
		TEST_METHOD(ConstructorTest1)
		{
			CModel* p_model = DBG_NEW CModel;
			Assert::AreEqual(0.0f, p_model->GetGameLevel(), EPSILON);
			Assert::AreEqual(0, p_model->GetNumOrbits());
			Assert::AreEqual(0, p_model->GetNumMonsters());
			Assert::AreEqual(0.0f, p_model->GetVOrbitron(), EPSILON);
			Assert::AreEqual(0.0f, p_model->GetVMonster(), EPSILON);
			delete p_model;
		}

		/* Tests constructor of CModel with argument */
		TEST_METHOD(ConstructorTest2)
		{
			std::string filename = "config_unittest.xml";
			CConfigurationData* p_config_data = DBG_NEW CConfigurationData(filename);
			CModel* p_model = DBG_NEW CModel(*p_config_data);
			Assert::AreEqual(0.0f, p_model->GetGameLevel(), EPSILON);
			Assert::AreEqual(p_config_data->GetOrbitNumber(), p_model->GetNumOrbits());
			Assert::AreEqual(p_config_data->GetMonsterNumber(), p_model->GetNumMonsters());
			Assert::AreEqual(p_config_data->GetOrbitronVelocity(), p_model->GetVOrbitron(), EPSILON);
			Assert::AreEqual(p_config_data->GetMonsterVelocity(), p_model->GetVMonster(), EPSILON);
			delete p_config_data, p_model;
		}

		/* Tests GenerateEntityOnRandomPoint() function of CModel */
		TEST_METHOD(EntityGenerationTest)
		{
			std::string filename = "config_unittest.xml";
			CConfigurationData* p_config_data = DBG_NEW CConfigurationData(filename);
			CModel* p_model = DBG_NEW CModel(*p_config_data);
			std::vector<E_ENTITY_TYPES> entity_types{ ENTITY_TYPES_ORBITRON , ENTITY_TYPES_MONSTER , ENTITY_TYPES_ROCKET , ENTITY_TYPES_ROCKET_RIGHT , ENTITY_TYPES_BOMB , ENTITY_TYPES_LIFE };
			for (INT32S i = 0; i < entity_types.size(); i++) {
				p_model->GenerateEntityOnRandomPoint(*p_config_data, entity_types[i]);
			}
			std::vector<std::shared_ptr<CEntity>> entity_list = p_model->GetEntityList();
			for (INT32S i = 0; i < entity_list.size(); i++) {
				Assert::AreEqual(static_cast<INT32S>(entity_types[i]), static_cast<INT32S>(entity_list[i]->GetEntityType()));
			}
			delete p_config_data, p_model;
		}

		/* Tests UpdateEntityList() function of CModel */
		TEST_METHOD(EntityListUpdateTest)
		{
			std::string filename = "config_unittest.xml";
			CConfigurationData* p_config_data = DBG_NEW CConfigurationData(filename);
			CModel* p_model = DBG_NEW CModel(*p_config_data);
			std::vector<E_ENTITY_TYPES> entity_types{ ENTITY_TYPES_ORBITRON , ENTITY_TYPES_MONSTER , ENTITY_TYPES_ROCKET , ENTITY_TYPES_ROCKET_RIGHT , ENTITY_TYPES_BOMB , ENTITY_TYPES_LIFE };
			std::vector<std::shared_ptr<CEntity>> p_entity_list;
			for (INT32S i = 0; i < entity_types.size(); i++) {
				p_model->GenerateEntityOnRandomPoint(*p_config_data, entity_types[i]);
				p_entity_list.push_back(p_model->GetEntityList()[i]);
			}

			p_entity_list[0]->SetIsAlive(false);
			p_entity_list[4]->SetIsAlive(false);
			p_entity_list[5]->SetIsAlive(false);
			p_model->SetEntityList(p_entity_list);
			std::vector<INT32S> deleted_entity_idx = p_model->UpdateEntityList();

			Assert::AreEqual(3, static_cast<INT32S>(deleted_entity_idx.size()));
			Assert::AreEqual(3, static_cast<INT32S>(p_model->GetEntityList().size()));
			Assert::AreEqual(0, deleted_entity_idx[0]);
			Assert::AreEqual(4, deleted_entity_idx[1]);
			Assert::AreEqual(5, deleted_entity_idx[2]);

			delete p_config_data, p_model;
		}
	};
}
