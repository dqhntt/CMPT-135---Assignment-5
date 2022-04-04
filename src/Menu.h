#ifndef MENU_H
#define MENU_H

#include "City.h"

enum class YesNo_Options { yes, no, invalid_option };
enum class Menu_Options { one, two, three, four, five, invalid_option };

class Menu {
public:
    Menu();
    ~Menu();

    // Returns any possible Menu_Options except invalid_option.
    Menu_Options get_input_option() const;

    void show_main_menu() const;

    // Sub-menus:

    class Add_records {
    public:
        void show_guides() const;
        City get_input() const;
        bool ask_if_user_wants_to_try_again() const;
        void say_record_exists(const City& city) const;
        void say_record_added(const City& city) const;
    } add_records;

    class Find_records {
    public:
        void by_string() const;
        void by_number() const;
    } find_records;

    class Delete_records {
    public:
        void by_string() const;
        void by_number() const;
    } delete_records;

    class List_records {
    public:
        void list() const;
    } list_records;

private:
    const time_t _start_time;
}; // class Menu

#endif // MENU_H