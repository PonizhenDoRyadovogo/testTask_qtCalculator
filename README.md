## О проекте
Приложение калькулятора на Qt. Реализовано с примением паттерна проектирования ```MVP (Model-View-Presenter)```

## Возможности
- Ввод чисел и десятичной точки
- Операции: `+`, `-`, `\`, `*`
- `CE` - очистка ввода
- `+\-` - смена знака числа
- `% ` - процент от числа
- `=` - вычисление результата
- Отображение вводимого выражения
- Отдельная строка для результата
- Обработка деления на 0 (окно с предупреждением)

*Примечание*: приоритет опреаций считается по порядку (то есть в примере `2 + 2 * 8` сначала вычислится `2 + 2 = 4`, затем `4 * 8 = 32`)

## UML-диаграмма классов
<img width="1791" height="1143" alt="qtCalculatorMVP drawio" src="https://github.com/user-attachments/assets/1a691823-47f7-4fcf-9399-1bd129b570d9" />

## Скриншоты программы
<img width="316" height="416" alt="Снимок экрана (1226)" src="https://github.com/user-attachments/assets/9390c6da-3e03-4347-bafb-d23996c347f7" />

<img width="314" height="413" alt="Снимок экрана (1227)" src="https://github.com/user-attachments/assets/87a9e3bb-90ab-4b09-9a77-3e0096ce6a83" />

<img width="316" height="417" alt="Снимок экрана (1228)" src="https://github.com/user-attachments/assets/e9157871-057c-4cae-a2e5-1bdbd2b82a11" />

## О приложении
**Qt**: `Qt 5.15.2`
**C++**: `C++17`
**Сборка**: `qmake` + `make`
**OS**: проверено на Ubuntu и Windows

```bash
sudo apt update
sudo apt install -y build-essential qt5-qmake qtbase5-dev qttools5-dev qttools5-dev-tools

qmake ../simple_calculator.pro
make -j"$(nproc)"
```

Запускаем файл:
```bash
./bin/simple_calculator
```
