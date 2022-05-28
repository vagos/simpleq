auto* coeffs = coefficients->getRawCoefficients();

auto b0 = coeffs[0];
auto b1 = coeffs[1];
auto b2 = coeffs[2];
auto a1 = coeffs[3];
auto a2 = coeffs[4];

auto lv1 = state[0];
auto lv2 = state[1];

for (size_t i = 0; i < numSamples; ++i)
{
    auto input = src[i];
    auto output = (input * b0) + lv1;
    dst[i] = bypassed ? input : output;

    lv1 = (input * b1) - (output* a1) + lv2;
    lv2 = (input * b2) - (output* a2);
}

util::snapToZero (lv1); state[0] = lv1;
util::snapToZero (lv2); state[1] = lv2;
