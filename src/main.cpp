#include <dpp/dpp.h>
#include <iostream>
#include <string>

// make sure the code can compile and work on an arm device.

int main(int argc,  char *argv[]) {
    // Try not to keep your token in the source code, also it might be bad that we are storing it in memory.
    if (argc < 2) {
        std::cout << "Please provide a bot token." << std::endl;
        return 1;
    }
    
    std::string token(argv[1]); // First value should be the bot token.
    dpp::cluster bot(token); 

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t &event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t &event)  {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("ping", "Ping pong!", bot.me.id)
            );
        } 
    });

    bot.start(dpp::st_wait);
}