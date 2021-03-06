#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <string>
#include "Inventory.hpp"
#include "Point.h"
#include "Engimon.hpp"
#include "Skill.h"

using namespace std;

class Player {
    private:
        string PlayerName;
        Point EngimonLocation; // Previous Location (Engimon mengikuti gerakan Player)
        Point Location; // Lokasi Player
        Inventory<Engimon> InvE; // Inventory Engimon (Kelas Engimon)
        Inventory<Skill> InvS; // Inventory SkillItem (Kelas Skill Item)
        Engimon* ActiveEngimon; // Pointer ke Active Engimon
        static int maxCapacity; // Kapasitas maksimum inventory
    public:
        Player(); // Default constructor
        Player(string name); // User-defined constructor
        Player(const Player &player); // Copy constructor
        Player& operator=(const Player&); // Operator Assignment
        ~Player(); // Destructor TEST
        Point getLocation(); // Getter Location Player
        Point getEngimonLocation(); // Getter Location Active Engimon
        Engimon* getActiveEngimon(); // Getter Active Engimon saat ini
        void Move(char direction); // Bergerak ke kiri, kanan, atas, atau bawah
        void CheckActive(); // Mengecek active engimon
        void SwitchActive(int index); // Mengganti active engimon // Mencari Engimon pada Inv dengan index
        void SwitchActiveMenu(); // Menu untuk memilih mengganti Engimon Active
        void PrintListEngimon(); // Menampilkan list engimon yang dimiliki
        // Menampilkan data lengkap suatu engimon (setiap atribut kelas)
        // Juga harus menampilkan nama parent beserta spesies mereka
        void PrintListSkillItem(); // Menampilkan list skill item yang dimiliki
        void PrintEngimonMenu(); // Print detail suatu Engimon (menampilkan nama parent beserta spesies mereka) serta seluruh atribut kelas
        void UseSkillItem(int indexS, int indexE); // Menggunakan skill item pada suatu engimon
        void UseSkillItemMenu(); // Menu menggunakan skill item
        void BreedingMenu(Engidex Engi); // Melaksanakan breeding antara 2 engimon
        // Petak kiri, kanan, atas, dan bawah (tampilkan detail engimon lawan ke layar)
        void Interact(); // Mengecek Active Engimon
        bool IsInventoryFull(); // Mengecek jika inventory full
        void InsertEngimon(Engimon E); // Insert Engimon ke inventory TEST
        void InsertSkillItem(Skill S); // Insert SkillItem ke inventory
        bool KillActive(); // Menghilangkan ActiveEngimon dari inventory, mengembalikan false jika inventory kosong (game over), true jika masih terdapat engimon
        void PrintInfo(); // Meng-outputkan info player
};

#endif