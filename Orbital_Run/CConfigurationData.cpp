#include "CConfigurationData.h"
using namespace rapidxml;

#define VDEFAULT_ENTITTY_VBOMB_RATIO    4.0f
#define VDEFAULT_ENTITTY_VLIFE_RATIO    3.0f

CConfigurationData::CConfigurationData()
{
	this->Filename = "config.xml";
	this->ConfigFileErrorStatus = false;
	this->XMLParser();
	this->OrbitronVelocity = this->OrbitronInitialVelocity;
	this->MonsterVelocity = this->MonsterInitialVelocity;
	this->BombVelocity = this->OrbitronInitialVelocity / VDEFAULT_ENTITTY_VBOMB_RATIO;
	this->RocketVelocity = this->OrbitronVelocity * this->RocketOrbitronVelocityRatio;
	this->RocketrightVelocity = DEFAULT_ROCKETRIGHT_VELOCITY;
	this->LifeVelocity = this->OrbitronInitialVelocity / VDEFAULT_ENTITTY_VLIFE_RATIO;
}

CConfigurationData::CConfigurationData(const CConfigurationData* config_data)
{
	this->OrbitronInitialVelocity = config_data->OrbitronInitialVelocity;
	this->MonsterInitialVelocity = config_data->MonsterInitialVelocity;
	this->RocketOrbitronVelocityRatio = config_data->RocketOrbitronVelocityRatio;
	this->VelocityIncreaseAtLevelUp = config_data->VelocityIncreaseAtLevelUp;
	this->MonsterOrbitChangeIntervalSec = config_data->MonsterOrbitChangeIntervalSec;
	this->MonsterSleepTimeSec = config_data->MonsterSleepTimeSec;
	this->OrbitronInitialLife = config_data->OrbitronInitialLife;
	this->OrbitNumber = config_data->OrbitNumber;
	this->MonsterNumber = config_data->MonsterNumber;
	this->ConstantLifeCount = config_data->ConstantLifeCount;
	this->ConstantBombAdditionCount = config_data->ConstantBombAdditionCount;
	this->RocketRightIntervalSec = config_data->RocketRightIntervalSec;
	this->BombAdditionIntervalSec = config_data->BombAdditionIntervalSec;
	this->BombRemovalIntervalSec = config_data->BombRemovalIntervalSec;
	this->LittlelifeNumForLife = config_data->LittlelifeNumForLife;
	this->OrbitronVelocity = config_data->OrbitronVelocity;
	this->MonsterVelocity = config_data->MonsterVelocity;
	this->BombVelocity = config_data->BombVelocity;
	this->RocketVelocity = config_data->RocketVelocity;
	this->RocketrightVelocity = config_data->RocketrightVelocity;
	this->LifeVelocity = config_data->LifeVelocity;
}

CConfigurationData::~CConfigurationData()
{

}

void CConfigurationData::XMLParser()
{
	xml_document<> doc;
	xml_node<>* root_node;

	try {
		std::ifstream file(this->Filename);
		if (file.fail()) {
			throw std::runtime_error("Configuration file (config.xml) couldn't be read.");
		}else {
			std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');
			doc.parse<0>(&buffer[0]);
			root_node = doc.first_node();
			xml_node<>* p_node = root_node->first_node();

			if (!strcmp("OrbitronInitialVelocity", p_node->first_attribute()->value())) {
				this->OrbitronInitialVelocity = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("MonsterInitialVelocity", p_node->first_attribute()->value())) {
				this->MonsterInitialVelocity = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("RocketOrbitronVelocityRatio", p_node->first_attribute()->value())) {
				this->RocketOrbitronVelocityRatio = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("VelocityIncreaseAtLevelUp", p_node->first_attribute()->value())) {
				this->VelocityIncreaseAtLevelUp = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("MonsterOrbitChangeIntervalSec", p_node->first_attribute()->value())) {
				this->MonsterOrbitChangeIntervalSec = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("MonsterSleepTimeSec", p_node->first_attribute()->value())) {
				this->MonsterSleepTimeSec = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("OrbitronInitialLife", p_node->first_attribute()->value())) {
				this->OrbitronInitialLife = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("OrbitNumber", p_node->first_attribute()->value())) {
				this->OrbitNumber = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("MonsterNumber", p_node->first_attribute()->value())) {
				this->MonsterNumber = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("ConstantLifeCount", p_node->first_attribute()->value())) {
				this->ConstantLifeCount = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("ConstantBombAdditionCount", p_node->first_attribute()->value())) {
				this->ConstantBombAdditionCount = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("RocketRightIntervalSec", p_node->first_attribute()->value())) {
				this->RocketRightIntervalSec = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("BombAdditionIntervalSec", p_node->first_attribute()->value())) {
				this->BombAdditionIntervalSec = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("BombRemovalIntervalSec", p_node->first_attribute()->value())) {
				this->BombRemovalIntervalSec = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("LittlelifeNumForLife", p_node->first_attribute()->value())) {
				this->LittlelifeNumForLife = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
		}
	}
	catch (const std::exception& exc) {
		this->ConfigFileErrorStatus = true;
		std::cout << "File error: " << exc.what() << "\n";
	}
}

void CConfigurationData::SetNumOrbits(INT32S num_orbit)
{
	this->OrbitNumber = num_orbit;
}

void CConfigurationData::SetNumMonsters(INT32S num_monster)
{
	this->MonsterNumber = num_monster;
}

void CConfigurationData::SetVOrbitron(FP32 v_orbitron)
{
	this->OrbitronVelocity = v_orbitron;
}

void CConfigurationData::SetVMonster(FP32 v_monster)
{
	this->MonsterVelocity = v_monster;
}

BOOLEAN CConfigurationData::GetConfigFileErrorStatus() const
{
	return this->ConfigFileErrorStatus;
}

INT32S CConfigurationData::GetNumOrbits() const
{
	return this->OrbitNumber;
}

INT32S CConfigurationData::GetNumMonsters() const
{
	return this->MonsterNumber;
}

FP32 CConfigurationData::GetVOrbitron() const
{
	return this->OrbitronVelocity;
}

FP32 CConfigurationData::GetVMonster() const
{
	return this->MonsterVelocity;
}

FP32 CConfigurationData::GetVBomb() const
{
	return this->BombVelocity;
}

FP32 CConfigurationData::GetVRocket() const
{
	return this->RocketVelocity;
}

FP32 CConfigurationData::GetVRocketRight() const
{
	return this->RocketrightVelocity;
}

FP32 CConfigurationData::GetVLife() const
{
	return this->LifeVelocity;
}