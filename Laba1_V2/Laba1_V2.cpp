#include <iostream> 
#include "locale.h" 

using namespace std;
int main()
{
    setlocale(0, "RUS");
    char* s = new char[100];
    int repeat_count;
    int index;
    char destination_buffer[512] = { 0 };
    bool infinity = true;
    while (infinity) {

        cout << ("\n Введите строку:\n");
        cin >> s;
        if (s[0] == '/') {
            infinity = false;

            return 0;
        }

        cout << ("\nВведите количество повторов:\n");
        cin >> repeat_count;

   
        if (repeat_count == 0) {
            cout << "\nВведенное значение равно 0\n";
            return 0;
        }

        else {
            if (repeat_count < 0) {
                cout << "\nВведенное значение меньше 0\n";

            }


            else {
                cout << ("\nВведите с какого символа выводить:\n");
                cin >> index;

                if (index == 0) {
                    cout << "\nВведенное значение равно 0\n";
                    return 0;
                }
                else {
                    if (index < 0) {
                        cout << "\nВведенное значение меньше 0\n";
                    }
                }


                int  index1 = strlen(s) - 1;
                char* index_string = new char[100];
                strcpy_s(index_string, 64, &s[index]);

                if (repeat_count > 0 && index > 0) {


                    _asm {
                        mov ecx, index1 // добавление итоговой строки в счетчик кол-во символов 
                        mov edi, index_string // добавление в приемник строки
                        sub al, al // обнуление регистра al

                        cld    /* Команда CLD (Clear DF) сбрасывает флаг в значение 0
                                   Флаг направления. Контролирует поведение команд обработки строк. Если установлен в 1,
                                    то строки обрабатываются в сторону уменьшения адресов, если сброшен в 0, то наоборот.*/

                                    repne scasb /* Повторить следующую строковую операцию, если не равно/Сравнить строку байтов
                                                            если обрабатываемая строковая операция — команда SCAS или CMPS,
                                                            то осуществляется проверка флага ZF, если условие повторения,
                                                            задаваемое префиксом (флаг ZF равен 1 для префикса REPE/REPZ или флаг ZF равен 0 для
                                                            префикса REPNE/REPNZ), не сохранилось, то выйти из цикла и перейти к следующей команде;
                                                            */
                                                            dec edi // -1 в приемнике
                                                            mov esi, index_string // добавление в источник строки
                                                            sub edi, esi    // вычитание источника из приемника(деление строки по кол-ву символов)
                                                            mov edx, edi    // перемещение значения из приемника в регистр данных
                                                            mov ecx, edi    // перемещение значения из приемника в счетчик

                                                            mov eax, repeat_count     // добавляем в регистр адресов количество повторений 
                                                            lea edi, destination_buffer       // записываем адресс buff в регистр  
                                                            Copy_loop : // маркер цикла
                        mov ecx, edx // перемещение значения из регистра данных в счетчик
                            rep movsb // Повторить следующую строковую операцию: Переслать байт из строки в строку
                            mov esi, index_string // перемещение значения из index string в источник
                            dec eax // -1 в аккумулятор
                            jnz Copy_loop // переход, если содержимое аккумулятора не равно нулю
                    }
                    cout << (destination_buffer);

                }
            }
        }
        cin.get();
    }
}
