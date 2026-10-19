#include <iostream>

using namespace std;

// Глобальна змінна для демонстрації глобального дозволу видимості імен
int g_nGlobalVar = 45;

int main()
{
    // Блочна структура та статичний розподіл
    cout << "1 & 2. Блокова структура та статичний розподіл" << endl;
    
    static int g_nStaticMain = 100; // Статична змінна в main
    int nLocalMain = 10;
    
    cout << "Main block: g_nStaticMain = " << g_nStaticMain 
              << ", nLocalMain = " << nLocalMain << endl;

    // Вкладений блок 1
    {
        static int g_nStaticNested = 200;
        int nLocalNested = 20;
        
        g_nStaticNested = g_nStaticNested + 50;
        cout << "Nested block 1: static = " << g_nStaticNested 
                  << ", local = " << nLocalNested << endl;
    }

    // Динамічний розподіл пам'яті в блоці (мембранний ефект)

    cout << "\n3.Динамічний розподіл у блоці (мембранний ефект)" << endl;
    
    int nMembraneVar = 5;
    cout << "Зовнішня nMembraneVar = " << nMembraneVar << endl;

    {
        // Мембранний ефект: перекриття змінної з однаковою назвою у вкладеному блоці
        int nMembraneVar = 777; 
        cout << "Внутрішня nMembraneVar (перекриття) = " << nMembraneVar << endl;
    }
    
    cout << "Після виходу з блоку nMembraneVar = " << nMembraneVar << endl;

    // Дослідження поведінки static та auto змінних у циклі
    cout << "\nДослідження циклу (static vs auto)" << endl;
    for (int i = 0; i < 5; i = i + 1)
    {
        static int iA = 0; // Зберігає значення між ітераціями
        auto   iB = 0; // Створюється та знищується на кожній ітерації
        
        iA = iA + 1;
        iB = iB + 1;
        
        cout << "Ітерація " << i << ": iA (static) = " << iA 
                  << ", iB (auto) = " << iB << endl;
    }

    // Глобальний дозвіл видимості імен (::)
    cout << "\n4. Глобальний дозвіл видимості імен (::)" << endl;
    
    double g_nGlobalVar = 10.1; // Локальна змінна перекриває глобальну
    
    cout << "Локальна g_nGlobalVar = " << g_nGlobalVar << endl;
    cout << "Глобальна g_nGlobalVar cherez (::) = " << ::g_nGlobalVar << endl;
    
    ::g_nGlobalVar = ::g_nGlobalVar * 2;
    cout << "Оновлена глобальна g_nGlobalVar = " << ::g_nGlobalVar << endl;

    // Динамічний розподіл пам'яті в «купі» (heap)
    cout << "\n5. Динамічний розподіл у купі" << endl;

    // Робота з першим покажчиком
    int* pFirstPointer = new int;
    if (pFirstPointer != nullptr) // Перевірка наявності вільної пам'яті
    {
        *pFirstPointer = 250;
        cout << "Початковий показник (&: " << &pFirstPointer 
                  << ", зміст: " << pFirstPointer 
                  << ", розіменування: " << *pFirstPointer << ")" << endl;
        
        delete pFirstPointer; // Своєчасне звільнення пам'яті
        pFirstPointer = nullptr;
    }

    // Другий покажчик (демонстрація витоку пам'яті / «сміття»)
    int* pSecondPointer = new int;
    *pSecondPointer = 500;
    cout << "Другий показник значення: " << *pSecondPointer << endl;
    
    // НЕ звільняємо пам'ять за допомогою delete pSecondPointer навмисно,
    // щоб продемонструвати утворення витоку пам'яті («сміття» в купі).
    pSecondPointer = nullptr; // Втрата адреси призводить до «сміття» в динамічній пам'яті!
    // Локальний покажчик у вкладеному блоці та утворення «сміття»
    {
        double* pLocalHeapVar = new double;
        *pLocalHeapVar = 99.99;
        // Якщо вийти з блоку без виклику delete pLocalHeapVar, 
        // покажчик знищиться, а виділена пам'ять в купі залишиться недоступною (витік).
        delete pLocalHeapVar; // коректне звільнення
    }

    return 0;
}