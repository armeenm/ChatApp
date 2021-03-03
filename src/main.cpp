#include <cstdlib>
#include <fmt/core.h>
#include <sleepy_discord/sleepy_discord.h>

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
  using SleepyDiscord::DiscordClient::DiscordClient;
  void onMessage(SleepyDiscord::Message message) override {
    if (message.startsWith("$hello"))
      sendMessage(message.channelID, "Hello " + message.author.username);
  }
};

int main() {
  fmt::print("Starting bot...\n");
  auto const token = std::getenv("DISCORD_BOT_TOKEN");
  fmt::print("Bot token: {}\n", token);

  auto client = MyClientClass{token, SleepyDiscord::USER_CONTROLED_THREADS};
  client.run();
}
