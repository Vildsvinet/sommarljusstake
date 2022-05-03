const model = require('../public/js/Model');

test("Sanity", () => {
    expect(true).toBe(true);
});

describe("Model interface", () => {
    const name = new model();

    test("defines lightOn()", () => {
        expect(typeof name.lightOn).toBe("boolean");
    })

    test('Light off default', () => {
        expect(name.lightOn).toBe(false)
    });
})

