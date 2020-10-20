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
	this->ConstantLifeNumber = config_data->ConstantLifeNumber;
	this->ConstantBombAdditionNumber = config_data->ConstantBombAdditionNumber;
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
			if (!strcmp("ConstantLifeNumber", p_node->first_attribute()->value())) {
				this->ConstantLifeNumber = std::stof(p_node->last_attribute()->value());
				p_node = p_node->next_sibling();
			}else {
				throw std::runtime_error("Corrupted config file (config.xml).");
			}
			if (!strcmp("ConstantBombAdditionNumber", p_node->first_attribute()->value())) {
				this->ConstantBombAdditionNumber = std::stof(p_node->last_attribute()->value());
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

void CConfigurationData::SetFilename(std::string filename)
{
	this->Filename = filename;
}
void CConfigurationData::SetConfigFileErrorStatus(BOOLEAN status)
{
	this->ConfigFileErrorStatus = status;
}
void CConfigurationData::SetOrbitronInitialVelocity(FP32 velocity)
{
	this->OrbitronInitialVelocity = velocity;
}
void CConfigurationData::SetMonsterInitialVelocity(FP32 velocity)
{
	this->MonsterInitialVelocity = velocity;
}
void CConfigurationData::SetRocketOrbitronVelocityRatio(FP32 ratio)
{
	this->RocketOrbitronVelocityRatio = ratio;
}
void CConfigurationData::SetVelocityIncreaseAtLevelUp(FP32 velocity_increase)
{
	this->VelocityIncreaseAtLevelUp = velocity_increase;
}
void CConfigurationData::SetMonsterOrbitChangeIntervalSec(FP32 interval)
{
	this->MonsterOrbitChangeIntervalSec = interval;
}
void CConfigurationData::SetMonsterSleepTimeSec(FP32 time)
{
	this->MonsterSleepTimeSec = time;
}
void CConfigurationData::SetOrbitronInitialLife(INT32S life)
{
	this->OrbitronInitialLife = life;
}
void CConfigurationData::SetOrbitNumber(INT32S orbit_number)
{
	this->OrbitNumber = orbit_number;
}
void CConfigurationData::SetMonsterNumber(INT32S monster_number)
{
	this->MonsterNumber = monster_number;
}
void CConfigurationData::SetConstantLifeNumber(INT32S num)
{
	this->ConstantLifeNumber = num;
}
void CConfigurationData::SetConstantBombAdditionNumber(INT32S num)
{
	this->ConstantBombAdditionNumber = num;
}
void CConfigurationData::SetRocketRightIntervalSec(INT32S interval)
{
	this->RocketRightIntervalSec = interval;
}
void CConfigurationData::SetBombAdditionIntervalSec(INT32S interval)
{
	this->BombAdditionIntervalSec = interval;
}
void CConfigurationData::SetBombRemovalIntervalSec(INT32S interval)
{
	this->BombRemovalIntervalSec = interval;
}
void CConfigurationData::SetLittlelifeNumForLife(INT32S littlelife_num)
{
	this->LittlelifeNumForLife = littlelife_num;
}
void CConfigurationData::SetOrbitronVelocity(FP32 velocity)
{
	this->OrbitronVelocity = velocity;
}
void CConfigurationData::SetMonsterVelocity(FP32 velocity)
{
	this->MonsterVelocity = velocity;
}
void CConfigurationData::SetBombVelocity(FP32 velocity)
{
	this->BombVelocity = velocity;
}
void CConfigurationData::SetRocketVelocity(FP32 velocity)
{
	this->RocketVelocity = velocity;
}
void CConfigurationData::SetRocketrightVelocity(FP32 velocity)
{
	this->RocketrightVelocity = velocity;
}
void CConfigurationData::SetLifeVelocity(FP32 velocity)
{
	this->LifeVelocity = velocity;
}

std::string CConfigurationData::GetFilename() const
{
	return this->Filename;
}
BOOLEAN CConfigurationData::GetConfigFileErrorStatus() const
{
	return this->ConfigFileErrorStatus;
}
FP32 CConfigurationData::GetOrbitronInitialVelocity() const
{
	return this->OrbitronInitialVelocity;
}
FP32 CConfigurationData::GetMonsterInitialVelocity() const
{
	return this->MonsterInitialVelocity;
}
FP32 CConfigurationData::GetRocketOrbitronVelocityRatio() const
{
	return this->RocketOrbitronVelocityRatio;
}
FP32 CConfigurationData::GetVelocityIncreaseAtLevelUp() const
{
	return this->VelocityIncreaseAtLevelUp;
}
FP32 CConfigurationData::GetMonsterOrbitChangeIntervalSec() const
{
	return this->MonsterOrbitChangeIntervalSec;
}
FP32 CConfigurationData::GetMonsterSleepTimeSec() const
{
	return this->MonsterSleepTimeSec;
}
INT32S CConfigurationData::GetOrbitronInitialLife() const
{
	return this->OrbitronInitialLife;
}
INT32S CConfigurationData::GetOrbitNumber() const
{
	return this->OrbitNumber;
}
INT32S CConfigurationData::GetMonsterNumber() const
{
	return this->MonsterNumber;
}
INT32S CConfigurationData::GetConstantLifeNumber() const
{
	return this->ConstantLifeNumber;
}
INT32S CConfigurationData::GetConstantBombAdditionNumber() const
{
	return this->ConstantBombAdditionNumber;
}
INT32S CConfigurationData::GetRocketRightIntervalSec() const
{
	return this->RocketRightIntervalSec;
}
INT32S CConfigurationData::GetBombAdditionIntervalSec() const
{
	return this->BombAdditionIntervalSec;
}
INT32S CConfigurationData::GetBombRemovalIntervalSec() const
{
	return this->BombRemovalIntervalSec;
}
INT32S CConfigurationData::GetLittlelifeNumForLife() const
{
	return this->LittlelifeNumForLife;
}
FP32 CConfigurationData::GetOrbitronVelocity() const
{
	return this->OrbitronVelocity;
}
FP32 CConfigurationData::GetMonsterVelocity() const
{
	return this->MonsterVelocity;
}
FP32 CConfigurationData::GetBombVelocity() const
{
	return this->BombVelocity;
}
FP32 CConfigurationData::GetRocketVelocity() const
{
	return this->RocketVelocity;
}
FP32 CConfigurationData::GetRocketrightVelocity() const
{
	return this->RocketrightVelocity;
}
FP32 CConfigurationData::GetLifeVelocity() const
{
	return this->LifeVelocity;
}
