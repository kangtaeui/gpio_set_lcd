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





# Process
<Clock Tree>
<img width="381" alt="clock" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/014be0a9-7d08-40ee-8d46-4256323a7a78">

## 1. RCC_CR register
<img width="397" alt="Process1-3" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/ca0cc1e1-b855-402d-93c7-9adf8828b8c8">

### 1-1) HSE ON
<img width="340" alt="process1" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/d3e538f9-c36b-4eee-8e82-9d59638473a1">

### 1-2) HSE Ready set by Hardware, so we wait for signal stable
![스크린샷 2024-03-21 093700](https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/b644bd4d-06b4-49e6-8de0-8f3edfeaa01f)

### 1-3) PLL ON & PLL READY
<img width="496" alt="PLLON_RDY" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/c92b19be-d49d-44da-a644-14c636fd5919">


## 2. PLL CONFIGURATION, RCC_PLLCFGR register (divide factor)
![Process2](https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/b87dabc1-0187-4b60-85a6-b8365b25eff1)
<img width="578" alt="PLL_CFGR Register" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/8aacba7b-cea7-4a22-837c-d16ab3ce222a">

### 2-1) PLLM
<img width="502" alt="PLLM" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/f782d2b9-d261-4032-9ed5-d581030e18a2">

### 2-2) PLLN
<img width="530" alt="PLLN" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/d857d8c7-1eae-4ec2-a393-d7f40adab273">

### 2-3) PLLR
<img width="494" alt="PLLR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/a77ce8f6-1150-40fc-8ef8-ac233752e127">

## 3. POWER ENABLE, FLASH SET
<img width="578" alt="LATENCY SET (HCLK" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/aaa8f49b-cf0b-4f33-93ea-a8c717fa4e0d">

### 3-1) RCC_APB1ENR
<img width="573" alt="RCC_APB1ENR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/f5a859c3-95da-4f64-afa6-e79e75ae638d">

### 3-2) PWR_CR VOS (SCALE SET), PWR_CR ODE (OVERDRIVE ON)
<img width="575" alt="PWR_CR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/e5f5076e-c058-4d87-a239-83627aba4df9">
<img width="550" alt="VOS, OVEERDRIVE" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/7aa4c3db-fdf1-4da9-88ed-dbbe20b1ffb8">

### 3-3) FLASH_ACR SET
<img width="581" alt="FLASH_ACR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/d401cd11-a44b-4de9-abae-d2189d715ed4">
<img width="499" alt="ACR_LATENCY" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/5c259559-eebb-42a7-8073-8c3fd7e632ee">

## 4. RCC_CFGR register ( PLLR SELECT )
<img width="580" alt="RCC_CFGR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/dc46d93b-f3b0-4037-9f1b-c743ffdfdfe1">

### 4-1) RCC_CFGR SET PLLR ON
<img width="501" alt="SWS,SWR PLLR SELECT" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/20a52671-8166-4847-be0e-c1d8a68f9c59">

### 4-2) HPRE SET
<img width="518" alt="HPRE" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/b46ff9fe-05e5-4dcd-a373-354838e08b34">

### 4-3) PPRE1 SET
<img width="525" alt="PPRE1" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/927bf744-dd1f-46be-b13d-373857c4e2fd">

## 5. GPIO ENABLE, RCC_AHB1ENR, GPIOA, GPIOB, GPIOH
<img width="578" alt="AHB1ENR" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/40821051-dd0e-4d3b-be44-6edfddf32b97">

### 5-1) Why use a GPIO PORT H? RCC OSC IN/OUT SET
<img width="475" alt="osc_in" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/f4890c54-a3ca-4d45-add5-198f963383d0">
<img width="568" alt="osc_in_out" src="https://github.com/kangtaeui/gpio_set_lcd/assets/141004174/bf238b01-3ef9-436e-a76e-128de575c1f4">

















