/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t ledPins[] = {LED0_Pin, LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin}; // LED'lerin tutulduğu array

#define LED_COUNT 5  // led sayısı 

#define led_delay 20  

enum LED_MODE {
      ALL_OFF = 0,
      ALL_ON,
      ALL_TOGGLE,
      KNIGHT_RIDER,
      RANDOM
    };

    enum LED_MODE currentMode = ALL_OFF;

enum CONTROL_MODE {
  AUTOMATIC = 0,
  MANUAL
};

enum CONTROL_MODE currentControlMode = AUTOMATIC;

int selectedLed = 0; // Manual modda hangi LED'in yanacağını tutar

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ALL LEDS OFF FUNC.
void all_leds_off(void){                     
  for(int i= 0; i < LED_COUNT; i++){
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_RESET);
  }
}

// ALL LEDS ON FUNC.
void all_leds_on(void){                     
  for(int i= 0; i < LED_COUNT; i++){
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_SET);
  }
}

// ALL LEDS TOGGLE FUNC.
void all_leds_toggle(void){                  
  for(int i= 0; i < LED_COUNT; i++){
    HAL_GPIO_TogglePin(GPIOA, ledPins[i]);
  }
  HAL_Delay(200);
}

// KNIGHT RIDER FUNC.
void leds_on_by_order(void){
  for (int i = 0; i < LED_COUNT; i++){
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_SET);
    HAL_Delay(led_delay);
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_RESET);
    HAL_Delay(led_delay);
  }

  for (int i = LED_COUNT-1; i > 0 ; i--){
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_SET);
    HAL_Delay(led_delay);
    HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_RESET);
    HAL_Delay(led_delay);
  }
}

void leds_random_on(void){

  
  int i = rand() % 5;

  HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_SET);
  HAL_Delay(led_delay);
  HAL_GPIO_WritePin(GPIOA, ledPins[i], GPIO_PIN_RESET);
  HAL_Delay(led_delay);

  
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    // ---  OTOMATİK MOD ---
    if (currentControlMode == 0) 
    {
        if(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(50);
            if(currentMode == 0) currentMode = 4; else currentMode--;
            all_leds_off();
            while(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET);
        }
        if(HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(50);
            currentMode++;
            if(currentMode > 4) currentMode = 0;
            all_leds_off();
            while(HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET);
        }

        // Efekt Switch-Case
        switch(currentMode){
          case 0: 
            all_leds_off(); 
            break;
          case 1: 
            all_leds_on(); 
            break;
          case 2: 
            all_leds_toggle(); 
            HAL_Delay(100); 
            break;
          case 3: 
            leds_on_by_order(); 
            break;
          case 4: 
            leds_random_on(); 
            break;
        }
    }
    
    // --- MANUEL MOD ---
    else if (currentControlMode == 1) 
    {
        // --- SOL BUTON KONTROLÜ ---
        if(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(100); // DİĞER BUTONU BEKLEME SÜRESİ
            
            if(HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET)
            {
                currentControlMode = 0; // İkisi de geldi, otomatiğe geç
                all_leds_off();
                while(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET || 
                      HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET);
            }
            else // Sadece sol basıldı
            {
                all_leds_off();
                if(selectedLed == 0) selectedLed = 4; else selectedLed--;
                while(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET);
            }
            HAL_Delay(50); // Bounce temizliği
        }

        // --- SAĞ BUTON KONTROLÜ ---
        if(HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(100); // BEKLEME SÜRESİ
            
            if(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET)
            {
                currentControlMode = 0; // İkisi de geldi, otomatiğe geç
                all_leds_off();
                while(HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == GPIO_PIN_RESET || 
                      HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET);
            }
            else // Sadece sağ basıldı
            {
                all_leds_off();
                selectedLed++;
                if(selectedLed > 4) selectedLed = 0;
                while(HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == GPIO_PIN_RESET);
            }
            HAL_Delay(50);
        }

        // Seçili LED'i yak
        if(currentControlMode == 1) HAL_GPIO_WritePin(GPIOA, ledPins[selectedLed], GPIO_PIN_SET);
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
