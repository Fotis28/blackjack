# Blackjack (C)

A console blackjack game written in C, with two wallets and betting. The player and the dealer
start with 100 each.The player bets, draws cards, and can raise the bet in the middle of a hand.
The dealer draws until reaching 17, as in the standard rules.

Cards are drawn from a real 52-card deck: every card that comes out is removed from the deck, so
the same card cannot appear twice. When fewer than 15 cards are left the deck is reshuffled
automatically, the way a shoe is replaced in a casino, so the game never stops for lack of cards.

## Features

- A single 52-card deck with the drawn cards tracked, and an automatic reshuffle below 15 cards
- Cards drawn are printed as small ASCII cards with the suit symbol; the dealer's cards are shown
  face down while the hand is in progress
- Betting from the player's wallet, with the bet checked against the wallet and against the
  dealer's wallet, and the option to raise the bet during the hand
- The player chooses whether an ace counts as 1 or 11; for the dealer the value is picked randomly
- Wallets, wins and losses are tracked across hands, and the game ends when a wallet reaches zero
- Every numeric input is validated, so letters or out-of-range values only cause the question to be
  asked again

## How to build and run

The code uses declarations inside `for` loops, so it needs C99 or newer:

```bash
gcc -std=c11 -Wall -Wextra -o blackjack blackjack.c
./blackjack
```

In Dev-C++ or Code::Blocks, set the compiler standard to C11 in the compiler options, otherwise
the build fails with "use option -std=c99 ... to compile your code".

## How to play

1. Answer `yes` to start a hand, or `no` to quit.
2. Enter your bet.
3. Then, for each turn:
   - `1` draws another card
   - `2` stands and passes the turn to the dealer
   - `3` raises the bet
4. The dealer draws until 17, the totals are compared and the pot goes to the winner. On a draw
   both players get their bet back.

## Known limitations

- Windows only: the game uses `system("pause")` and `system("cls")`, and the suit symbols rely on
  the code page of the Windows console
- The hand does not start with two cards as in real blackjack; the player draws one card at a time
  from an empty hand
- Splitting, doubling down and insurance are not implemented, and a natural blackjack (21 on the
  first two cards) does not pay more than a normal win
- The dealer plays a fixed strategy: draw until 17, with no reaction to the player's hand

## Author

First-year university project, written in C.

- **[Fotis Singiridis](https://github.com/Fotis28)**

## License

Copyright (c) 2026 Fotis Singiridis. All rights reserved.

This code is published for portfolio purposes: you are welcome to read it and run it locally,
but it may not be reused, redistributed or used commercially without permission.
See [LICENSE](LICENSE).
