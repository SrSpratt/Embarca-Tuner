set(SRC_FILES
    ADC.c
    Interfaces.c
    ssd1306.c
    FFT.c
)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC_FILES}
)