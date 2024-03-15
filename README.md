# Turn on LCD without module( lcd don't have scl, sda communication pin )

![KakaoTalk_20240314_170734876](https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/831c38de-a542-4d5d-b4d0-05f711754f00)

# Ioc

<img width="399" alt="GPIO_SET" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/4887120d-4dd4-42bb-a67f-79be1ec104e7">

# System clock

<img width="643" alt="IOC_MX" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/e24cd8f0-b9a9-4c5b-82f7-f4bcb380b596">




*위의 설정대로 RCC_CLOCK과 주파수에 따른 FLASH_ACR을 맞춰주었고, COMPILE을 실행하면서 REGISTER 주소에 접근하여 기능을 뭘 키고 뭘 꺼야할지 숙지한 후에 주소로 접근하여 켜야할 곳에 FLAG를 표시하여 켜주는 것이 좋다.*
*Register에 Flag를 세워줄 때 or 연산을 써야할지 =을 써야할지 고려해보는 것이 좋다. 그렇지만 레지스터에 flag를 세우는 것이니까 그냥 =을 써도 무방할 것 같다. 내 것에서 |=이 통했던 이유는 초기 value값이 0x00000000일 것 같다. 테스트 필요함* 



