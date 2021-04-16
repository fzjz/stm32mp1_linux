#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>

struct gpio_desc *testio;

static int gpio_init_probe(struct platform_device *pdev)
{
   int i = 0;
printk("GPIO example init\n");

   testio = devm_gpiod_get(&pdev->dev, "testio", GPIOD_OUT_LOW);
//only for test
   while (i < 10)
   {
	ssleep(1);
	gpiod_set_value(testio, 1);

	ssleep(1);
	gpiod_set_value(testio, 0);
	
	i++;
   }
   return(0);
}

static int gpio_exit_remove(struct platform_device *pdev)
{
   
   return(0);
}

static struct of_device_id dummy_match[] = {
    {.compatible = "myir,testio"},
    {/* end node */}
};

static struct platform_driver dummy_driver = {
    .probe = gpio_init_probe,
    .remove = gpio_exit_remove,
    .driver = {
        .name = "dummy_driver",
                .owner = THIS_MODULE,
                .of_match_table = dummy_match,
    }
};
 
module_platform_driver(dummy_driver);

MODULE_DESCRIPTION("Gpio example");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dummy_driver");
