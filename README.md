# Turn on LCD without a module( lcd don't have scl, sda communication pins )

![KakaoTalk_20240314_170734876](https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/831c38de-a542-4d5d-b4d0-05f711754f00)

# Ioc

<img width="399" alt="GPIO_SET" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/4887120d-4dd4-42bb-a67f-79be1ec104e7">

# System clock

<img width="643" alt="IOC_MX" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/e24cd8f0-b9a9-4c5b-82f7-f4bcb380b596">




* 위의 설정대로 RCC_CLOCK과 주파수에 따른 FLASH_ACR을 맞춰주었고, COMPILE을 실행하면서 REGISTER 주소에 접근하여 기능을 뭘 키고 뭘 꺼야할지 숙지한 후에 주소로 접근하여 켜야할 곳에 FLAG를 표시하여 켜주는 것이 좋다
* Register에 Flag를 세워줄 때 연산을 잘 고려해야 한다.
* 예를 들어 GPIOA->MODER를 13번만 켜주고 나머지는 원래 VALUE값이 뭐였던 건드리기 싫은 경우인데 아래와같이 코딩해주면 된다. ( PA13 DDR SET )
* #define GPIOA_MODE  GPIOA->MODER //GPIOA->MODER를 GPIOA_MODE로 쓰겠다.
* GPIOA_MODE = (GPIOA_MODE & 0x3fffffff) | 0x80000000;  //GPIOA의 원래 값에 13번핀을 00으로 &연산 후에 13번핀에 10을 OR연산하여 0x10xxxxxx로 만들어주겠다.



