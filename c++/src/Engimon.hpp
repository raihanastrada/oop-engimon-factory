#ifndef _ENGIMON_HPP_
#define _ENGIMON_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

#include "Point.h"
#include "Skill.h"
#include "Elements.hpp"

using namespace std;

// ENGIMON DIES AT LEVEL 100.
#define MAX_EXP 100 * 100 
#define LINEx(n) cout << "------" << n << "------" << endl;

/*
ENGIDEX code format
<first-element 1..5> <second-element 0..5> <index 0..10>

example:
Third engimon type with elements Electric and Fire has ENGIDEX code:
    1203

First engimon type with elements Ground
    3001
*/

// ASUMSI HANYA ADA SATU ENGIDEX UNTUK SATU GAME.
class Engidex {
    public:
        Engidex()
        {
            codex = map<int, Species>();
        }

        Engidex(const Engidex &eng) 
        {
            codex = eng.codex;
        }

        Engidex& operator=(const Engidex &e)
        {
            codex = e.codex;
            return *this;
        }

        class Species {
            private:
                int species_id;
                string species_name;
            protected:
                vector<Skill> skills;
                vector<Element> elements;
            public:
                Species()
                {
                    species_name = "Unknown";
                    species_id = 0;
                }

                Species(Engidex e, int id)
                {
                    Species spec = e.getSpecies(id);
                    species_name = spec.species_name;
                    species_id = spec.species_id;
                    skills = spec.skills;
                    elements = spec.elements;
                };

                /* Constructors for creating new species and entering into codex */
                Species(string nm, int id, Skill u, Element e1) 
                {
                    species_name = nm;
                    species_id = id;
                    skills.push_back(u);
                    elements.push_back(e1);
                };

                Species(string nm, int id, Skill u, Element e1, Element e2)
                {
                    species_name = nm;
                    species_id = id;
                    skills.push_back(u);
                    elements.push_back(e1);
                    elements.push_back(e2);
                };

                Species(string nm, int id, Skill u, vector<Element> a)
                {
                    species_name = nm;
                    species_id = id;
                    skills.push_back(u);
                    elements = a;
                };

                // Copy constructor
                Species(const Species &spec)
                {
                    species_name = spec.species_name;
                    species_id = spec.species_id;
                    skills = spec.skills;
                    elements = spec.elements;
                }

                void species_info_print() 
                {
                    cout << species_name << endl;
                }

                string getSpeciesName() { return species_name; };
                int getEngidexID() { return species_id; };
                Skill getUniqueSkill() { return skills[0]; };

                vector<Element> getElements() { return elements; };

                Species& operator=(const Species& sp)
                {
                    if (this != &sp){
                        species_name = sp.species_name;
                        species_id = sp.species_id;
                        skills = sp.skills;
                        elements = sp.elements;
                    }
                    return *this;
                };

                bool operator==( Species sp2 ) { return species_id == sp2.species_id; };
                bool operator==( int id ) { return species_id == id; };
                bool operator==( string name ) { return species_name == name; };
        };
        
        void addSpecies(string name, int id, Skill u, Element a1, Element a2)
        {
            Species s(name, id, u, a1, a2);
            codex.insert(make_pair(id, s));
        };

        void addSpecies(string name, int id, Skill u, string a1, string a2)
        {
            Species s(name, id, u, Element(a1), Element(a2));
            codex.insert(make_pair(id, s));
        };

        void addSpecies(string name, int id, Skill u, Element a1)
        {
            Species s(name, id, u, a1);
            codex.insert(make_pair(id, s));
        };

        void addSpecies(string name, int id, Skill u, string a1)
        {
            Species s(name, id, u, Element(a1));
            codex.insert(make_pair(id, s));
        };

        void addSpecies(string name, int id, Skill u, vector<Element> a)
        {
            Species s(name, id, u, a);
            codex.insert(make_pair(id, s));
        }

        // friend void addNewEntry(string name, int code, )
        // {
        //     Skill shock(1, 1, vector<Element>() = { electric });
        //     addSpecies("Pikamee", 1001, shock, electric);
        // }

        Species getSpecies(int code) {
            return codex[code];
        }

    private:
        map<int, Species> codex;
};

/*
Relasi inheritance IS A,
Engimon bernama "PikaPika" dengan spesies "Pikachu" maka, PikaPika(child, engimon) IS A Pikachu(parent, species)
*/

class Engimon : public Engidex::Species {
    private:
        int                 id;
        string              name;
        vector<Engimon*>    parents;
        int                 exp;
        int                 level;
        bool                alive;

        static long long int engimon_count;
    public:
        Engimon()
        {
            name = "UNKNOWN";
            exp = 0;
            level = 0;
            alive = false;
        }

        Engimon(Engidex e, int species_id) : Species(e, species_id)
        {
            id = engimon_count;
            engimon_count++;
            name = getSpeciesName();
            // skills.push_back(getUniqueSkill());
            exp = 0;
            level = 0;
            alive = true;
        };

        Engimon(const Engimon &e) : Species(e)
        {
            id = e.id;
            name = e.name;
            parents = e.parents;
            skills = e.skills;
            exp = e.exp;
            level = e.level;
            alive = e.alive;
        }

        Engimon& operator=(const Engimon &e)
        {
            if (this != &e){
                Species::operator=(e);
                id = e.id;
                name = e.name;
                parents = e.parents;
                skills = e.skills;
                exp = e.exp;
                level = e.level;
                alive = e.alive;
            }
            return *this;
        }

        ~Engimon()
        {
            vector<Engimon*>().swap(parents);
            vector<Skill>().swap(skills);
        };

        /* SETTERS */
        void setName(string new_name)
        {   
            name = new_name;
        };
        
        void setLevel(int new_level)
        {
        	level = new_level;
		}
		
		void setParents(Engimon* dad, Engimon* mom)
		{
			parents.push_back(dad);
			parents.push_back(mom);
		}

        /* GETTERS */
        bool    getAlive()              { return alive; };
        string  getName()               { return name; };
        int     getLevel()              { return level; };
        int     getExp()                { return exp % 100; };
        int     getCumulativeExp()      { return exp; };

        /* BASIC FUNCTIONS */
        void addExp(int new_exp)
        {
            if (exp + new_exp > MAX_EXP)
            {
                exp = MAX_EXP;
                alive = false;
            } else {
                exp += new_exp;
                if ((new_exp + getExp()) > 100)
                {
                    level++;
                }
                exp += new_exp;
            }
        };

        void PrintInfo()
        {
             cout << getEngidexID() << "#" << getSpeciesName() << "\t" << " \"" << name << "\"";
        };

        bool addSkill(Skill newSkill)
        {
            if (!newSkill.isCompatible(elements)) { cout << "SkillItem not compatible with " << name << endl; return false; }
            // if (newSkill.getMasteryLevel())
            if (skills.size() < 4 && (find(skills.begin(), skills.end(), newSkill) == skills.end()))
            {
                skills.push_back(newSkill);
                cout << name << " learnt a new skill!" << endl; 
                return true;
            } else {
                if (find(skills.begin(), skills.end(), newSkill) != skills.end()) { cout << name << " already knows that skill" << endl; return false; }
                int x;
                cout << name << " already has 4 skills, choose a skill to replace: " << endl;
                for (int i = 0; i < skills.size(); i++) {
                    cout << (i + 1) << ". " << skills.at(i).getName() << endl;
                }
                cout << endl << "Skill to replace: ";
                cin >> x;
                if ((x - 1) < 0 || (x - 1) >= skills.size()) {cout << "Input not valid" << endl; return false;}
                skills.erase(skills.begin() + (x - 1));
                skills.push_back(newSkill);
                cout << "Skill replaced, " << name << " learnt a new skill!" << endl;
                return true;
            }
        };
		
		void addSkillBreed(Skill newSkill)
		{
			if (newSkill.isCompatible(elements)) {
				if (skills.size() < 4 && (find(skills.begin(), skills.end(), newSkill) == skills.end())) {
					skills.push_back(newSkill);
				}
				else if (skills.size() == 4) {
					vector<Skill> temp;
					for (int i=1;i<skills.size();i++) {
						if (skills[i]<newSkill) {
							temp.push_back(skills.at(i));
							skills.erase(skills.begin() + i);
							skills.push_back(newSkill);
							break;
						}
					}
					if (temp.size()>0) { // cek seluruh skill lagi
						for (int i=1;i<skills.size();i++) {
							sort(temp.rbegin(),temp.rend());
							if (skills.at(i)<temp.at(0)) {
								temp.push_back(skills.at(i));
								skills.erase(skills.begin() + i);
								skills.push_back(temp.at(0));
								temp.erase(temp.begin() + 0);
							}
						}
					}
				}
				else if (find(skills.begin(), skills.end(), newSkill) != skills.end()) {
					for (int i=0;i<skills.size();i++) {
						if (skills.at(i) == newSkill) {
							if (skills.at(i).getMasteryLevel() == newSkill.getMasteryLevel()) {
								skills.at(i).setMasteryLevel(skills.at(i).getMasteryLevel() + 1);
							}
							else if (skills.at(i) < newSkill) {
								skills.erase(skills.begin() + i);
								skills.push_back(newSkill);
							}
						}
					}
				}
			}
		}
		
        void PrintDetail() {
            cout << "Details: " << endl;
            PrintInfo(); cout << endl;
            cout << "ID: " << id << endl;
            cout << "Level: " << level << endl;
            cout << "EXP: " << exp << endl;
            cout << "Status: Alive" << endl;
            cout << "Skills: ";
            for (int i = 0; i < skills.size(); i++) {
                cout << skills.at(i).getName();
                cout << " MLvl: ";
                cout << skills.at(i).getMasteryLevel();
                cout << " BPow: ";
                cout << skills.at(i).getBasePower();
                if (i != skills.size() - 1) { cout << ", "; } 
            }
            cout << endl;
            cout << "Elements: ";
            for (int i = 0; i < elements.size(); i++) {
                cout << elements.at(i).getName();
                if (i != elements.size() - 1) { cout << ", "; }
            }
            cout << endl;
            cout << "Parents: ";
            if (parents.size() == 0) { cout << "NONE" << endl; return; }
            for (int i = 0; i < parents.size(); i++) {
                parents.at(i)->PrintInfo();
                if (i != parents.size() - 1) { cout << ", "; }
            }
            cout << endl;
        }

        vector<Skill> getSkills(){
            return skills;
        }

        /* OPERATORS */
        bool operator==(Engimon comp) { return id == comp.id; };

        /* FRIEND FUNCTIONS */
        friend Engimon breed(Engimon* dad, Engimon* mom, Engidex e); // for breeding
};

#endif
